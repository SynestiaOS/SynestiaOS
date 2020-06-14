#ifndef __LIBRARY_LIBC_STDLIB_H__
#define __LIBRARY_LIBC_STDLIB_H__

#include <stdint.h>

#define MIN(x, y) (((x) < (y) ? (x) : (y)))
#define MAX(x, y) (((x) < (y) ? (y) : (x)))

void memcpy(void *dest, const void *src, uint32_t bytes);

void bzero(void *dest, uint32_t bytes);
void memset(void *dest, uint8_t c, uint32_t bytes);


void putc(char c);
void puts(const char *str);
void print(const char *str);

#endif // __LIBRARY_LIBC_STDLIB_H__
