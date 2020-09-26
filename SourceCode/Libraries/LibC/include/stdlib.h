#ifndef __LIBRARY_LIBC_STDLIB_H__
#define __LIBRARY_LIBC_STDLIB_H__

#include <stdint.h>
#include <stdarg.h>

#define DEFAULT_STRING_LEN 256

void reverse(char str[], int length);

void memclean(uint8_t *start, const uint8_t *end);

void bzero(void *s1, uint32_t n);

char *printf(const char *format,...);

#endif// __LIBRARY_LIBC_STDLIB_H__
