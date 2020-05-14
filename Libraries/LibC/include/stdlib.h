#ifndef __LIBRARY_LIBC_STDLIB_H__
#define __LIBRARY_LIBC_STDLIB_H__

#include <stdint.h>

#define MIN(x, y) (((x) < (y) ? (x) : (y)))
#define MAX(x, y) (((x) < (y) ? (y) : (x)))

void memcpy(void *dest, const void *src, int bytes);

void bzero(void *dest, int bytes);
void memset(void *dest, uint8_t c, int bytes);

char *itoa(int number, int scale);

void putc(char c);
void puts(const char *str);
void print(const char *str);
void printf(const char *fmt, ...);

#endif // __LIBRARY_LIBC_STDLIB_H__
