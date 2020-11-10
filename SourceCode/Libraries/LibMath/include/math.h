//
// Created by XingfengYang on 2020/7/12.
//

#ifndef __LIBRARY_LIBMATH_MATH_H__
#define __LIBRARY_LIBMATH_MATH_H__

#include "macros.h"

EXTERN_C float fmod(float r, float mod);

EXTERN_C float cosf(float angle);

EXTERN_C float sinf(float angle);

float tanf(float angle);

float fmax(float x, float y);

EXTERN_C float powf(float x, float y);

float q_rsqrt(float number);

#endif//__LIBRARY_LIBMATH_MATH_H__
