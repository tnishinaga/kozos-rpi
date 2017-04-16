#include "defines.h"
#include "kozos.h"
#include "intr.h"
#include "interrupt.h"
#include "serial.h"
#include "lib.h"
#include "consdrv.h"

#define CONS_BUFFER_SIZE 24

static struct consreg {
  kz_thread_id_t id; /* コンソールを利用するスレッド */
  int index;         /* 利用するシリアルの番号 */

  char *send_buf;    /* 送信バッファ */
  char *recv_buf;    /* 受信バッファ */
  int send_len;      /* 送信バッファ中のデータサイズ */
  int recv_len;      /* 受信バッファ中のデータサイズ */

  /* kozos.c の kz_msgbox と同様の理由で，ダミー・メンバでサイズ調整する */
  long dummy[3];
} consreg[CONSDRV_DEVICE_NUM];

/*
 * 以下の２つの関数(send_char(), send_string())は割込み処理とスレッドから
 * 呼ばれるが送信バッファを操作しており再入不可のため，スレッドから呼び出す
 * 場合は排他のため割込み禁止状態で呼ぶこと．
 */

/* 送信バッファの先頭１文字を送信する */
static void send_char(struct consreg *cons)
{
  int i;
  serial_send_byte(cons->index, cons->send_buf[0]);
  cons->send_len--;
  /* 先頭文字を送信したので，１文字ぶんずらす */
  for (i = 0; i < cons->send_len; i++)
    cons->send_buf[i] = cons->send_buf[i + 1];
}

/* 文字列を送信バッファに書き込み送信開始する */
static void send_string(struct consreg *cons, char *str, int len)
{
  int i;
  for (i = 0; i < len; i++) { /* 文字列を送信バッファにコピー */
    if (str[i] == '\n') /* \n→\r\nに変換 */
      cons->send_buf[cons->send_len++] = '\r';
    cons->send_buf[cons->send_len++] = str[i];
  }
  /*
   * 送信割込み無効ならば，送信開始されていないので送信開始する．
   * 送信割込み有効ならば送信開始されており，送信割込みの延長で
   * 送信バッファ内のデータが順次送信されるので，何もしなくてよい．
   */
  if (cons->send_len && !serial_intr_is_send_enable(cons->index)) {
    serial_intr_send_enable(cons->index); /* 送信割込み有効化 */
    send_char(cons); /* 送信開始 */
  }
}

/*
 * 以下は割込みハンドラから呼ばれる割込み処理であり，非同期で
 * 呼ばれるので，ライブラリ関数などを呼び出す場合には注意が必要．
 * 基本として，以下のいずれかに当てはまる関数しか呼び出してはいけない．
 * ・再入可能である．
 * ・スレッドから呼ばれることは無い関数である．
 * ・スレッドから呼ばれることがあるが，割込み禁止で呼び出している．
 * また非コンテキスト状態で呼ばれるため，システム・コールは利用してはいけない．
 * (サービス・コールを利用すること)
 */
static int consdrv_intrproc(struct consreg *cons)
{
  unsigned char c;
  char *p;

  if (serial_is_recv_enable(cons->index)) { /* 受信割込み */
    c = serial_recv_byte(cons->index);
    if (c == '\r') /* 改行コード変換(\r→\n) */
      c = '\n';

    send_string(cons, &c, 1); /* エコーバック処理 */

    if (cons->id) {
      if (c != '\n') {
	/* 改行でないなら，受信バッファにバッファリングする */
	cons->recv_buf[cons->recv_len++] = c;
      } else {
	/*
	 * Enterが押されたら，バッファの内容を
	 * コマンド処理スレッドに通知する．
	 * (割込みハンドラなので，サービス・コールを利用する)
	 */
	p = kx_kmalloc(CONS_BUFFER_SIZE);
	memcpy(p, cons->recv_buf, cons->recv_len);
	kx_send(MSGBOX_ID_CONSINPUT, cons->recv_len, p);
	cons->recv_len = 0;
      }
    }
  }

  if (serial_is_send_enable(cons->index)) { /* 送信割込み */
    if (!cons->id || !cons->send_len) {
      /* 送信データが無いならば，送信処理終了 */
      serial_intr_send_disable(cons->index);
    } else {
      /* 送信データがあるならば，引続き送信する */
      send_char(cons);
    }
  }

  return 0;
}

/* 割込みハンドラ */
static void consdrv_intr(void)
{
  int i;
  struct consreg *cons;

  for (i = 0; i < CONSDRV_DEVICE_NUM; i++) {
    cons = &consreg[i];
    if (cons->id) {
      if (serial_is_send_enable(cons->index) ||
	  serial_is_recv_enable(cons->index))
	/* 割込みがあるならば，割込み処理を呼び出す */
	consdrv_intrproc(cons);
    }
  }
}

static int consdrv_init(void)
{
  memset(consreg, 0, sizeof(consreg));
  return 0;
}

/* スレッドからの要求を処理する */
static int consdrv_command(struct consreg *cons, kz_thread_id_t id,
			   int index, int size, char *command)
{
  switch (command[0]) {
  case CONSDRV_CMD_USE: /* コンソール・ドライバの使用開始 */
    cons->id = id;
    cons->index = command[1] - '0';
    cons->send_buf = kz_kmalloc(CONS_BUFFER_SIZE);
    cons->recv_buf = kz_kmalloc(CONS_BUFFER_SIZE);
    cons->send_len = 0;
    cons->recv_len = 0;
    serial_init(cons->index);
    serial_intr_recv_enable(cons->index); /* 受信割込み有効化(受信開始) */
    break;

  case CONSDRV_CMD_WRITE: /* コンソールへの文字列出力 */
    /*
     * send_string()では送信バッファを操作しており再入不可なので，
     * 排他のために割込み禁止にして呼び出す．
     */
    INTR_DISABLE;
    send_string(cons, command + 1, size - 1); /* 文字列の送信 */
    INTR_ENABLE;
    break;

  default:
    break;
  }

  return 0;
}

int consdrv_main(int argc, char *argv[])
{
  int size, index;
  kz_thread_id_t id;
  char *p;

  consdrv_init();
  kz_setintr(SOFTVEC_TYPE_SERINTR, consdrv_intr); /* 割込みハンドラ設定 */

  while (1) {
    id = kz_recv(MSGBOX_ID_CONSOUTPUT, &size, &p);
    index = p[0] - '0';
    consdrv_command(&consreg[index], id, index, size - 1, p + 1);
    kz_kmfree(p);
  }

  return 0;
}
