//
// Created by XingfengYang on 2020/7/30.
//

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

char *strcpy(char *des, char *source) {
  char *r = des;
  while ((*r++ = *source++) != '\0')
    ;
  return des;
}

uint32_t strlen(const char *str) {
  const char *ptr = str;
  while (*str++)
    ;
  return (str - ptr - 1);
}

void *memset(char *s, int c, uint32_t n) {
  char *tmpS = (char *)s;
  while (n-- > 0)
    *tmpS++ = c;
  return s;
}

void memcpy(void *dest, const void *src, uint32_t bytes) {
  char *d = dest;
  const char *s = src;
  while (bytes--) {
    *d++ = *s++;
  }
}

char *itoa(int num, char *str, int base) {
  int i = 0;
  _Bool isNegative = false;

  if (num == 0) {
    str[i] = '0';
    return str;
  }

  if (num < 0 && base == 10) {
    isNegative = true;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (isNegative) {
    str[i++] = '-';
  }

  reverse(str, i);

  return str;
}
