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
    __test_all_asserts = 0;                             \
    __test_failed_asserts = 0;                          \
    printf("\n\033[32m[TEST] %s:\033[0m\n",text);       \
    func();

#define ASSERT_EQ(left, right) do{ assert(left==right); }while(0)
#define ASSERT_NEQ(left, right) do{ assert(left!=right); }while(0)
#define ASSERT_TRUE(value) do{ assert(value); }while(0)
#define ASSERT_FALSE(value) do{ assert(!value); }while(0)
#define ASSERT_EQ_FLOAT(left, right, sill) do{assert(abs(left-right)< sill);}while(0)

#endif //__KERNEL_TEST_H__
