//
// Created by XingfengYang on 2020/7/12.
//
#include "libmath/math.h"

float fmod(float x, float y) { return __builtin_fmod(x, y); }

float cosf(float x) { return __builtin_cosf(x); }

float sinf(float x) { return __builtin_sinf(x); }

float tanf(float angle) { return __builtin_sinf(angle) / __builtin_cosf(angle); }

float fmax(float x, float y) { return x > y ? x : y; }

float powf(float x, float y) { return __builtin_powf(x, y); }

/**
 * This Q_rsqrt code is from JohnCarmark
 * https://en.wikipedia.org/wiki/John_Carmack
 * @param number
 * @return
 */
float q_rsqrt(float number) {
    long i = 0;
    float x2 = 0;
    float y = 0;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *) &y;         // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);// what the fuck?
    y = *(float *) &i;
    y = y * (threehalfs - (x2 * y * y));// 1st iteration
    //    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

unsigned int abs(int number) {
    return number < 0 ? -number : number;
}

