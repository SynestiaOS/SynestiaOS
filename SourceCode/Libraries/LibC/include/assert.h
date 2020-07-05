//
// Created by XingfengYang on 2020/7/5.
//

#ifndef __LIBRARY_LIBC_ASSERT_H__
#define __LIBRARY_LIBC_ASSERT_H__


#include <stdlib.h>

extern uint32_t __test_failed_asserts;
extern uint32_t __test_all_asserts;


void __assert_func_failed(const char *file, int line, const char *func, const char *failedexpr) {
    __test_all_asserts++;
    __test_failed_asserts++;
    printf("    └──\033[31mAssertion \"%s\" false \033[0m\n", failedexpr);
    printf("        ├──\033[31mFile: %s, Line: %d \033[0m\n", file, line);
    printf("        └──\033[31mFunction: %s \033[0m\n", func);
}

void __assert_func_success(const char *file, int line, const char *func, const char *failedexpr) {
    __test_all_asserts++;
    printf("    └──\033[32mAssertion \"%s\" true \033[0m\n", failedexpr);
}

# define assert(__e) \
    ((__e) \
        ? __assert_func_success( \
            __FILE__, \
            __LINE__, \
            __PRETTY_FUNCTION__, \
            #__e)  \
        : __assert_func_failed( \
            __FILE__, \
            __LINE__, \
            __PRETTY_FUNCTION__, \
            #__e) \
    )

#endif //__LIBRARY_LIBC_ASSERT_H__
