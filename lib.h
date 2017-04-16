#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

void *memset(void *b, int c, long len);
void *memcpy(void *dst, const void *src, long len);
int memcmp(const void *b1, const void *b2, long len);
int strlen(const char *s);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int len);

int putc(unsigned char c);    /* １文字送信 */
unsigned char getc(void);     /* １文字受信 */
int puts(unsigned char *str); /* 文字列送信 */
int gets(unsigned char *buf); /* 文字列受信 */
int putxval(unsigned long value, int column); /* 数値の16進表示 */

#endif
