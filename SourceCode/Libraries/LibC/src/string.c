//
// Created by Shifu Wu  on 2020/7/4.
//

#include <string.h>

size_t strlen(const char *str) {
  size_t len = 0;
  while (*str++ != '\0') {
    ++len;
  }
  return len;
}

int strncmp(const char *src, const char *dest, uint32_t size) { return 0; }

char *strncat(char *str, const char *x, uint32_t size) { return str; }

int strcmp(const char *src, const char *dest) { return 0; }

int memcmp(const void *lhs, const void *rhs, uint32_t count) {
  return 0;
}
