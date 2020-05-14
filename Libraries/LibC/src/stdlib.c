#include <uart.h>

#include <stdint.h>
#include <stdlib.h>

void memcpy(void *dest, const void *src, int bytes) {
  char *d = dest;
  const char *s = src;
  while (bytes--) {
    *d++ = *s++;
  }
}

void bzero(void *dest, int bytes) { memset(dest, 0, bytes); }

void memset(void *dest, uint8_t c, int bytes) {
  uint8_t *d = dest;
  while (bytes--) {
    *d++ = c;
  }
}

char *itoa(int number, int scale) {
  if (number == 0) {
    return "0\0";
  }

  static char buf[32] = {0};

  int i = 30;
  const char characters[] = "0123456789abcdef";
  for (; number && i; --i, number /= scale) {
    buf[i] = characters[number % scale];
  }
  return &buf[i + 1];
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

void printf(const char *fmt, ...) {
  __builtin_va_list args;
  __builtin_va_start(args, fmt);
  for (; *fmt != '\0'; fmt++) {
    if (*fmt == '%') {
      switch (*(++fmt)) {
      case '%':
        putc('%');
        break;
      case 'd':
        puts(itoa(__builtin_va_arg(args, int), 10));
        break;
      case 'x':
        puts(itoa(__builtin_va_arg(args, int), 16));
        break;
      case 's':
        puts(__builtin_va_arg(args, char *));
        break;
      }
    } else {
      putc(*fmt);
    }
  }
  __builtin_va_end(args);
}
