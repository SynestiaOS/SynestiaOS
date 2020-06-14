#include <uart.h>

#include <stdint.h>
#include <stdlib.h>

void memcpy(void *dest, const void *src, uint32_t bytes) {
  char *d = dest;
  const char *s = src;
  while (bytes--) {
    *d++ = *s++;
  }
}

void bzero(void *dest, uint32_t bytes) { memset(dest, 0, bytes); }

void memset(void *dest, uint8_t c, uint32_t bytes) {
  uint8_t *d = dest;
  while (bytes--) {
    *d++ = c;
  }
}


void putc(char c) { uart_putc(c); }

void puts(const char *str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    putc(str[i]);
  }
}

void print(const char *str) {
  while (*str) {
    putc(*str);
    str++;
  }
}
