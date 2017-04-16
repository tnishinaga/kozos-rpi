#ifndef _INTERRUPT_H_INCLUDED_
#define _INTERRUPT_H_INCLUDED_

/* 以下はリンカ・スクリプトで定義してあるシンボル */
extern char _softvec;
#define SOFTVEC_ADDR (&_softvec)

typedef short softvec_type_t;

typedef void (*softvec_handler_t)(softvec_type_t type, unsigned long sp);

#define SOFTVECS ((softvec_handler_t *)SOFTVEC_ADDR)

// #define INTR_ENABLE  asm volatile ("andc.b #0x3f,ccr")
// #define INTR_DISABLE asm volatile ("orc.b #0xc0,ccr")
// TODO: ARM対応
#define INTR_ENABLE  asm volatile ("nop")
#define INTR_DISABLE asm volatile ("nop")

/* ソフトウエア・割込みベクタの初期化 */
int softvec_init(void);

/* ソフトウエア・割込みベクタの設定 */
int softvec_setintr(softvec_type_t type, softvec_handler_t handler);

/* 共通割込みハンドラ */
void interrupt(softvec_type_t type, unsigned long sp);

#endif
