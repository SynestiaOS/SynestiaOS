//
// Created by XingfengYang on 2020/7/5.
//

#ifndef __KERNEL_TEST_H__
#define __KERNEL_TEST_H__

#include <assert.h>

#define TEST_SUIT(text, func)                                   \
    printf("\n\033[32m[TEST] %s:\033[0m\n",text);       \
    func();

#define ASSERT_EQ(left, right){ assert(left==right); }
#define ASSERT_NEQ(left, right){ assert(left!=right); }
#define ASSERT_TRUE(value){ assert(value); }
#define ASSERT_FALSE(value){ assert(!value); }
#define ASSERT_EQ_FLOAT(left, right, sill) {assert(abs(left-right)< sill);}

#endif //__KERNEL_TEST_H__
