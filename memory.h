#ifndef _KOZOS_MEMORY_H_INCLUDED_
#define _KOZOS_MEMORY_H_INCLUDED_

int kzmem_init(void);        /* 動的メモリの初期化 */
void *kzmem_alloc(int size); /* 動的メモリの獲得 */
void kzmem_free(void *mem);  /* メモリの解放 */

#endif
