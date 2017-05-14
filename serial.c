#include "defines.h"
#include "serial.h"
#include "rpi_peripherals.h"

/* デバイス初期化 */
int serial_init(int index)
{
  	// UART無効化
	*UART0_CR 	= 0;
	
	//ポートの設定
	// GPIO14: ALT0
  // GPIO15: ALT0
  *GPFSEL1 &= ~((uint32)0x07 << ((14 % 10) * 3));
  *GPFSEL1 &= ~((uint32)0x07 << ((15 % 10) * 3));
  *GPFSEL1 |= ((uint32)0x04 << ((14 % 10) * 3));
  *GPFSEL1 |= ((uint32)0x04 << ((15 % 10) * 3));

  // 割り込みフラグのクリア
  *UART0_ICR = 0x7ff;

  // ボーレートの設定(9600)
  *UART0_IBRD = 19;
  *UART0_FBRD = 34;

  // LCRH
	// stick parity dis, 8bit, FIFO en, two stop bit no, odd parity, parity dis, break no
	*UART0_LCRH = 3 << 5;

	// CR
	// CTS dis, RTS dis, OUT1-2=0, RTS dis, DTR dis, RXE en, TXE en, loop back dis, SIRLP=0, SIREN=0, UARTEN en
	*UART0_CR 	= 0x0301;

  // UART割り込みを有効化
  // UARTのIRQ番号は57
  *INTERRUPT_ENABLE_IRQS2 = ((uint32)1 << (57 % 32));

  return 0;
}

/* 送信可能か？ */
int serial_is_send_enable(int index)
{
  // check FR:TXFF
  return (*UART0_FR & (1 << 5)) ? 0:1;
}

/* １文字送信 */
int serial_send_byte(int index, unsigned char c)
{
  *UART0_DR = c;
  return 0;
}

/* 受信可能か？ */
int serial_is_recv_enable(int index)
{
  // check FR:RXFE
  return (*UART0_FR & (1 << 4)) ? 0:1;
}

/* １文字受信 */
unsigned char serial_recv_byte(int index)
{
  return (*UART0_DR & 0xff);
}

/* 送信割込み有効か？ */
int serial_intr_is_send_enable(int index)
{
  // Raspberry Pi で割り込みを有効にするためには以下の2つを行う必要がある
  // * IRQレジスタを使ったUART自体の割り込み有効化
  // * UARTレジスタの割り込みマスク設定
  // 前者はinit処理時に行うので必要なし
  // 後者のみを行う
  return (*UART0_IMSC & ((uint32)1 << 5)) ? 1 : 0;
}

/* 送信割込み有効化 */
void serial_intr_send_enable(int index)
{
  *UART0_IMSC |= (uint32)1 << 5;
}

/* 送信割込み無効化 */
void serial_intr_send_disable(int index)
{
  *UART0_IMSC &= ~((uint32)1 << 5);
}

/* 受信割込み有効か？ */
int serial_intr_is_recv_enable(int index)
{
  return (*UART0_IMSC & ((uint32)1 << 4)) ? 1 : 0;
}

/* 受信割込み有効化 */
void serial_intr_recv_enable(int index)
{
  *UART0_IMSC |= (uint32)1 << 4;
}

/* 受信割込み無効化 */
void serial_intr_recv_disable(int index)
{
  *UART0_IMSC &= ~((uint32)1 << 4);
}
