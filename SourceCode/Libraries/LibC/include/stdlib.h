#ifndef __LIBRARY_LIBC_STDLIB_H__
#define __LIBRARY_LIBC_STDLIB_H__

#include <stdint.h>

#define DEFAULT_STRING_LEN 256

void reverse(char str[], int length);

void memclean(uint8_t *start, const uint8_t *end);

void bzero(void *s1, uint32_t n);

void put_char(char c);

void print(const char *str);

int printf(const char *format, ...);

#endif // __LIBRARY_LIBC_STDLIB_H__
