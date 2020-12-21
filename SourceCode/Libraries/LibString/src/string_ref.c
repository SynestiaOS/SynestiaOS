//
// Created by XingfengYang on 2020/12/19.
//
#include "libstring/string_ref.h"
#include "libc/stdint.h"
#include "libc/string.h"

StringRef string_ref(const char *str) {
    struct StringRef ref = {
            .length = strlen(str),
            .str = str,
            .pos = 0,
    };
    return ref;
}

StringRef string_ref_slice(const char *str, uint32_t pos, uint32_t length) {
    uint32_t len = strlen(str);
    if (pos >= len) {
        struct StringRef ref = {
                .length = len,
                .str = str,
                .pos = 0,
        };
        return ref;
    } else if (pos + length >= len) {
        struct StringRef ref = {
                .length = len - pos,
                .str = str,
                .pos = pos,
        };
        return ref;
    } else {
        struct StringRef ref = {
                .length = length,
                .str = str,
                .pos = pos,
        };
        return ref;
    }
}

bool string_ref_equal(struct StringRef str1, struct StringRef str2) {
    if (str1.length != str2.length) {
        return false;
    }
    for (uint32_t i = 0; i < str1.length; i++) {
        if (str1.str[str1.pos + i] != str2.str[str2.pos + i]) {
            return false;
        }
    }
    return true;
}

