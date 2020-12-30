#include "libc/stdlib.h"
#include "libc/stdint.h"
#include "raspi2/uart.h"

void memclean(uint8_t *start, const uint8_t *end) {
  uint32_t i;
  for (i = 0; start + i < end; i++) {
    *(start + i) = '\0';
  }
}

void bzero(void *s1, uint32_t n) {
  register char *t = s1;

  while (n != 0) {
    *t++ = 0;
    n--;
  }
}

void reverse(char str[], int length) {
  char t;
  char *start = str;
  char *end = &str[length - 1];
  while (start < end) {
    t = *start;
    *start = *end;
    *end = t;
    start++;
    end--;
  }
}

static char buf[1024] = {0};
int32_t sprintf(char*buffer, char *fmt, ...) {
    va_list args;
    int32_t i;
    va_start(args, fmt);
    i = vsprintf(buffer, fmt, args);
    va_end(args);
    return i;
}

int32_t printf(const char *fmt, ...) {
    va_list args;
    int32_t i = 0;
    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);
    uart_print(buf);
    bzero(buf, 1024);
    return i;
}
