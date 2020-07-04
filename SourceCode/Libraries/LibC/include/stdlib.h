#ifndef __LIBRARY_LIBC_STDLIB_H__
#define __LIBRARY_LIBC_STDLIB_H__

#include <stdint.h>

#define DEFAULT_STRING_LEN 256

void memclean(uint8_t *start, const uint8_t *end);

char *strcpy(char *des, char *source);

void memcpy(void *dest, const void *src, uint32_t bytes);

void put_char(char c);

void print(const char *str);

int printf(const char *format, ...);

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

void exit(int exit_code);

void abort();

#ifndef NULL
#define NULL (void *)0
#endif

#endif // __LIBRARY_LIBC_STDLIB_H__
