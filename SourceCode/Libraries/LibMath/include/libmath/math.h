//
// Created by XingfengYang on 2020/7/12.
//

#ifndef __LIBRARY_LIBMATH_MATH_H__
#define __LIBRARY_LIBMATH_MATH_H__

#include "libc/macros.h"

float fmod(float r, float mod);

float cosf(float angle);

float sinf(float angle);

float tanf(float angle);

float fmax(float x, float y);

float powf(float x, float y);

float q_rsqrt(float number);

unsigned  int abs(int);

#endif//__LIBRARY_LIBMATH_MATH_H__
