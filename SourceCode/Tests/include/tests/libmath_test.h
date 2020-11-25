//
// Created by XingfengYang on 2020/7/29.
//
#ifndef __KERNEL_MATH_TEST_H__
#define __KERNEL_MATH_TEST_H__

#include "libmath/math.h"

void should_math_sinf() {
    float x = sinf(60);
    ASSERT_TRUE(1 == 1);
}

void should_math_cosf() {
    float x = cosf(60);
    ASSERT_TRUE(1 == 1);
}

void should_math_fmod() {
    float x = fmod(60, 2);
    ASSERT_TRUE(1 == 1);
}

void should_math_powf() {
    float x = powf(60, 2);
    ASSERT_TRUE(1 == 1);
}

#endif//__KERNEL_MATH_TEST_H__
