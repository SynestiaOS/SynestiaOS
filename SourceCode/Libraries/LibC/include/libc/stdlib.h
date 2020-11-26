#ifndef __LIBRARY_LIBC_STDLIB_H__
#define __LIBRARY_LIBC_STDLIB_H__

#include "libc/macros.h"
#include "libc/stdarg.h"
#include "libc/stdint.h"

#define DEFAULT_STRING_LEN 256

void reverse(char str[], int length);

extern_C void memclean(uint8_t *start, const uint8_t *end);

void bzero(void *s1, uint32_t n);

int32_t vsprintf(char *buf, const char *fmt, va_list args);

int32_t printf(const char *format, ...);

#endif// __LIBRARY_LIBC_STDLIB_H__
