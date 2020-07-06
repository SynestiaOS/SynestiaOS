//
// Created by XingfengYang on 2020/7/5.
//

#ifndef __KERNEL_TEST_H__
#define __KERNEL_TEST_H__

#include <stdlib.h>

static uint32_t __test_all_asserts = 0;
static uint32_t __test_failed_asserts = 0;

void __assert_func_failed(const char *file, int line, const char *func, const char *failedexpr);


void __assert_func_success(const char *file, int line, const char *func, const char *failedexpr);

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

#define TEST_SUIT(text, func)                           \
    printf("\n\033[32m[TEST] %s:\033[0m\n",text);       \
    func();

#define ASSERT_EQ(left, right){ assert(left==right); }
#define ASSERT_NEQ(left, right){ assert(left!=right); }
#define ASSERT_TRUE(value){ assert(value); }
#define ASSERT_FALSE(value){ assert(!value); }
#define ASSERT_EQ_FLOAT(left, right, sill) {assert(abs(left-right)< sill);}

#endif //__KERNEL_TEST_H__
