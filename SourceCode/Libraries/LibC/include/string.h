//
// Created by Shifu Wu  on 2020/7/4.
//

#pragma once

#include <stdint.h>

size_t strlen(const char *str);

int strncmp(const char *, const char *, uint32_t);

char *strncat(char *__restrict, const char *__restrict, uint32_t);

int strcmp(const char *, const char *);

void *memset(void *dest, int ch, size_t count);

int memcmp(const void *lhs, const void *rhs, uint32_t count);
