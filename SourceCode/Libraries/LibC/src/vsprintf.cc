#include <libc/stdint.h>
#include <libc/stdlib.h>
#include <libc/string.h>

#define is_digit(c) ((c) >= '0' && (c) <= '9')

static int skip_atoi(const char **s) {
    int i = 0;
    while (is_digit(**s))
        i = i * 10 + *((*s)++) - '0';
    return i;
}

#define ZEROPAD 1
#define SIGN 2
#define PLUS 4
#define SPACE 8
#define LEFT 16
#define SPECIAL 32
#define SMALL 64

int32_t do_div(int *n, int base) {
    int32_t res = 0;
    res = *n % base;
    *n = *n / base;
    return res;
}

static char *number(char *str, int num, int base, int size, int precision,
                    int type) {
    char c, sign, tmp[36];
    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    if (type & SMALL)
        digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (type & LEFT)
        type &= ~ZEROPAD;
    if (base < 2 || base > 36)
        return 0;
    c = (type & ZEROPAD) ? '0' : ' ';
    if (type & SIGN && num < 0) {
        sign = '-';
        num -= num;
    } else
        sign = (type & PLUS) ? '+' : ((type & SPACE) ? ' ' : 0);
    if (sign)
        size--;
    if (type & SPECIAL) {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
        while (num != 0)
            tmp[i++] = digits[do_div(&num, base)];
    if (i > precision)
        precision = i;
    size -= precision;
    if (!(type & (ZEROPAD + LEFT)))
        while (size-- > 0)
            *str++ = ' ';
    if (sign)
        *str++ = sign;
    if (type & SPECIAL) {
        if (base == 8)
            *str++ = '0';
        else if (base == 16) {
            *str++ = '0';
            *str++ = digits[33];// 'X' 或 'x'
        }
    }
    if (!(type & LEFT))
        while (size-- > 0) {
            *str++ = c;
        }
    while (i < precision--) {
        *str++ = '0';
    }
    while (i-- > 0) {
        *str++ = tmp[i];
    }
    while (size-- > 0) {
        *str++ = ' ';
    }
    return str;
}

int32_t vsprintf(char *buf, const char *fmt, va_list args) {
    int32_t len;
    int32_t i;
    char *str;
    char *s;
    int32_t *ip;
    uint32_t flags;
    int32_t field_width;
    int32_t precision;
    int32_t qualifier
            __attribute__((unused));

    for (str = buf; *fmt; ++fmt) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }
        flags = 0;
    repeat:
        ++fmt;
        switch (*fmt) {
            case '-':
                flags |= LEFT;
                goto repeat;
            case '+':
                flags |= PLUS;
                goto repeat;
            case ' ':
                flags |= SPACE;
                goto repeat;
            case '#':
                flags |= SPECIAL;
                goto repeat;
            case '0':
                flags |= ZEROPAD;
                goto repeat;
        }
        field_width = -1;
        if (is_digit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*') {
            field_width = va_arg(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }
        precision = -1;
        if (*fmt == '.') {
            ++fmt;
            if (is_digit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*') {
                // it's the next argument
                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }
        qualifier = -1;
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
            qualifier = *fmt;
            ++fmt;
        }
        switch (*fmt) {
            case 'c':
                if (!(flags & LEFT))
                    while (--field_width > 0)
                        *str++ = ' ';
                *str++ = (uint8_t) va_arg(args, int);
                while (--field_width > 0)
                    *str++ = ' ';
                break;
            case 's':
                s = va_arg(args, char *);
                len = strlen(s);
                if (precision < 0)
                    precision = len;
                else if (len > precision)
                    len = precision;
                if (!(flags & LEFT))
                    while (len < field_width--)
                        *str++ = ' ';
                for (i = 0; i < len; ++i)
                    *str++ = *s++;
                while (len < field_width--)
                    *str++ = ' ';
                break;
            case 'o':
                str = number(str, va_arg(args, uint32_t), 8, field_width, precision,
                             flags);
                break;
            case 'p':
                if (field_width == -1) {
                    field_width = 8;
                    flags |= ZEROPAD;
                }
                str = number(str, (uint32_t) va_arg(args, void *), 16, field_width,
                             precision, flags);
                break;
            case 'x':
                flags |= SMALL;
                __attribute__((fallthrough));
            case 'X':
                str = number(str, va_arg(args, uint32_t), 16, field_width,
                             precision, flags);
                break;
            case 'd':
            case 'i':
                flags |= SIGN;
                __attribute__((fallthrough));
            case 'u':
                str = number(str, va_arg(args, uint32_t), 10, field_width,
                             precision, flags);
                break;
            case 'n':
                ip = va_arg(args, int *);
                *ip = (str - buf);
                break;
            default:
                if (*fmt != '%')
                    *str++ = '%';
                if (*fmt)
                    *str++ = *fmt;
                else
                    --fmt;
                break;
        }
    }
    *str = '\0';
    return str - buf;
}
