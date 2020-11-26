//
// Created by XingfengYang on 2020/7/30.
//
#include "libc/stdint.h"

uint32_t adler32(const char *buf, uint32_t buflength) {
    const uint8_t *buffer = (const uint8_t *) buf;

    uint32_t s1 = 1;
    uint32_t s2 = 0;

    for (uint32_t n = 0; n < buflength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) | s1;
}
