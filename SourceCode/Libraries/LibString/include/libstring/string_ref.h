//
// Created by XingfengYang on 2020/12/19.
//

#ifndef SYNESTIAOS_STRING_REF_H
#define SYNESTIAOS_STRING_REF_H

#include "libc/stdbool.h"
#include "libc/stdint.h"

typedef struct StringRef {
    const char *str;
    uint32_t pos;
    uint32_t length;
} StringRef;

StringRef string_ref(const char *str);

StringRef string_ref_slice(const char *str, uint32_t pos, uint32_t length);

bool string_ref_equal(struct StringRef str1, struct StringRef str2);

void string_ref_print(struct StringRef str);

#endif//SYNESTIAOS_STRING_REF_H
