#include <uart.h>

#include <stdint.h>
#include <stdlib.h>

#include <stdarg.h>

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

char getOffsetFromString(char *formatStr, int32_t offset) {
    return *(formatStr + offset);
}

uint32_t getArgsNumFromFormatString(const char *formatStr) {
    char * tmp = formatStr;
    uint32_t num = 0;
    while (*tmp) {
        if (*tmp == '%') {
            if (getOffsetFromString(tmp, 1) == 'd') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'u') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 's') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'f') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'e') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'x') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'o') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'g') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'p') {
                num++;
            }
            if (getOffsetFromString(tmp, 1) == 'l') {
                if (getOffsetFromString(tmp, 2) == 'u') {
                    num++;
                }
                if (getOffsetFromString(tmp, 2) == 'x') {
                    num++;
                }
                if (getOffsetFromString(tmp, 2) == 'l') {
                    if (getOffsetFromString(tmp, 3) == 'u') {
                        num++;
                    }
                    if (getOffsetFromString(tmp, 3) == 'x') {
                        num++;
                    }
                }
            }
        }
        tmp++;
    }
    return num;
}


int printf(const char *format, ...) {

    va_list valist;

    uint32_t num = getArgsNumFromFormatString(format);

    int i;
    va_start(valist, num);
    char * tmp = format;
    while (*tmp) {
        if (*tmp == '%') {
            if (getOffsetFromString(tmp, 1) == 'd') {
                int value = va_arg(valist, int);

            }
            if (getOffsetFromString(tmp, 1) == 'u') {
            }
            if (getOffsetFromString(tmp, 1) == 's') {
            }
            if (getOffsetFromString(tmp, 1) == 'f') {
            }
            if (getOffsetFromString(tmp, 1) == 'e') {
            }
            if (getOffsetFromString(tmp, 1) == 'x') {
            }
            if (getOffsetFromString(tmp, 1) == 'o') {
            }
            if (getOffsetFromString(tmp, 1) == 'g') {
            }
            if (getOffsetFromString(tmp, 1) == 'p') {
            }
            if (getOffsetFromString(tmp, 1) == 'l') {
                if (getOffsetFromString(tmp, 2) == 'u') {
                }
                if (getOffsetFromString(tmp, 2) == 'x') {
                }
                if (getOffsetFromString(tmp, 2) == 'l') {
                    if (getOffsetFromString(tmp, 3) == 'u') {
                    }
                    if (getOffsetFromString(tmp, 3) == 'x') {
                    }
                }
            }
        }
        tmp++;
    }
    va_end(valist);

    return 0;
}
