//
// Created by XingfengYang on 2020/7/12.
//

#ifndef __LIBRARY_LIBMATH_MATH_H__
#define __LIBRARY_LIBMATH_MATH_H__

#include "libc/macros.hpp"

extern_C float fmod(float r, float mod);

extern_C float cosf(float angle);

extern_C float sinf(float angle);

float tanf(float angle);

float fmax(float x, float y);

extern_C float powf(float x, float y);

float q_rsqrt(float number);

#endif//__LIBRARY_LIBMATH_MATH_H__
