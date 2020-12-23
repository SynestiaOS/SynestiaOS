//
// Created by XingfengYang on 2020/12/23.
//

#include "kernel/assert.h"
#include "libc/stdlib.h"

void __assert_fail(const char *file, int line, const char *failedExpr) {
    printf("[ASSERT_FAILED]: %s at %s (%d)\n", failedExpr, file, line);
}

void __assert_fail_msg(const char *file, int line, const char *failedExpr, const char *msg) {
    printf("[ASSERT_FAILED]: %s with msg :'%s' at %s (%d)\n", failedExpr, msg, file, line);
}
