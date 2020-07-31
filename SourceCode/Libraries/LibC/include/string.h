//
// Created by XingfengYang on 2020/7/30.
//
#ifndef __LIBRARY_LIBC_STRING_H__
#define __LIBRARY_LIBC_STRING_H__
#include <stdint.h>

char *strcpy(char *des, char *source);

uint32_t strlen(const char *str);

char *itoa(int num, char *str, int base);

void *memset(char *s, int c, uint32_t n);

void memcpy(void *dest, const void *src, uint32_t bytes);

#endif // __LIBRARY_LIBC_STRING_H__
