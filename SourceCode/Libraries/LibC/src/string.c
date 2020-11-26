//
// Created by XingfengYang on 2020/7/30.
//

#include "libc/stdint.h"
#include "libc/stdlib.h"
#include "libc/string.h"
#include "libc/stdbool.h"

char *strcpy(char *des, char *source) {
    char *r = des;
    while ((*r++ = *source++) != '\0')
        ;
    return des;
}

_Bool strcmp(char *str1, char *str2) {
    char *tmpStr1 = str1;
    char *tmpStr2 = str2;
    uint32_t str1Len = strlen(tmpStr1);
    uint32_t str2Len = strlen(tmpStr2);
    if (str1Len != str2Len) {
        return false;
    }

    if (str1Len < str2Len) {
        while (*tmpStr1) {
            if (*tmpStr1 == *tmpStr2) {
                tmpStr1++;
                tmpStr2++;
            } else {
                return false;
            }
        }
        return true;
    } else {
        while (*tmpStr2) {
            if (*tmpStr2 == *tmpStr1) {
                tmpStr2++;
                tmpStr1++;
            } else {
                return false;
            }
        }
        return true;
    }
}

uint32_t strlen(const char *str) {
    const char *ptr = str;
    uint32_t len = 0;
    while (*ptr) {
        len++;
        ptr++;
    }
    return len;
}

void *memset(char *s, int c, uint32_t n) {
    char *tmpS = (char *) s;
    while (n-- > 0) {
        *tmpS++ = c;
    }
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
    bool isNegative = false;

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
