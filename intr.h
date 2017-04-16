#ifndef _INTR_H_INCLUDED_
#define _INTR_H_INCLUDED_

/* ソフトウエア・割込みベクタの定義 */

#define SOFTVEC_TYPE_NUM     3

#define SOFTVEC_TYPE_SOFTERR 0
#define SOFTVEC_TYPE_SYSCALL 1
#define SOFTVEC_TYPE_SERINTR 2

#endif
