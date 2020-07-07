#include <uart.h>

#include <stdint.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stdbool.h>

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

char *strcpy(char *des, char *source) {
    char *r = des;
    while ((*r++ = *source++) != '\0');
    return des;
}

void memcpy(void *dest, const void *src, uint32_t bytes) {
    char *d = dest;
    const char *s = src;
    while (bytes--) {
        *d++ = *s++;
    }
}

void put_char(char c) {
    uart_put_char(c);
}

void print(const char *str) {
    while (*str) {
        put_char(*str);
        str++;
    }
}

char getOffsetFromString(char *formatStr, int32_t offset) {
    return *(formatStr + offset);
}

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

int printf(const char *format, ...) {

    va_list valist;

    uint32_t num = getArgsNumFromFormatString(format);

    char result[DEFAULT_STRING_LEN];
    for (int i = 0; i < DEFAULT_STRING_LEN; i++) {
        result[i] = '\0';
    }
    char *resultPtr = &result;
    va_start(valist, num);

    char *tmp = format;
    while (*tmp) {
        if (*tmp == '%') {
            if (getOffsetFromString(tmp, 1) == 'd') {
                // 1. get argument from args
                int value = va_arg(valist, int);

                // 2. covert int to string and append at tail
                char int32s[10];
                char *intStr = itoa(value, &int32s, 10);
                while (*intStr) {
                    *resultPtr = *intStr;
                    intStr++;
                    resultPtr++;
                }

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'u') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 's') {
                // 1. get argument from args
                char *value = va_arg(valist, char*);
                while (*value) {
                    *resultPtr = *value;
                    value++;
                    resultPtr++;
                }
                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'f') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'e') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'x') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'o') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'g') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'p') {

                tmp += 2;
                continue;
            }
            if (getOffsetFromString(tmp, 1) == 'l') {
                if (getOffsetFromString(tmp, 2) == 'u') {

                    tmp += 3;
                    continue;
                }
                if (getOffsetFromString(tmp, 2) == 'x') {

                    tmp += 3;
                    continue;
                }
                if (getOffsetFromString(tmp, 2) == 'l') {
                    if (getOffsetFromString(tmp, 3) == 'u') {

                        tmp += 4;
                        continue;
                    }
                    if (getOffsetFromString(tmp, 3) == 'x') {

                        tmp += 4;
                        continue;
                    }
                }
            }
        } else {
            *resultPtr = *tmp;
            resultPtr++;
        }
        tmp++;
    }
    va_end(valist);


    print(result);

    return 0;
}
