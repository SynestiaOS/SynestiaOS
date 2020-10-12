#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>
#include <uart.h>

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

char getOffsetFromString(char *formatStr, int32_t offset) { return *(formatStr + offset); }

uint32_t getArgsNumFromFormatString(const char *formatStr) {
    char *tmp = formatStr;
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

static char buf[1024];

int32_t printf(const char *fmt,...) {
    va_list args;
    int     i;
    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);
    uart_print(buf);
    return i;
}
