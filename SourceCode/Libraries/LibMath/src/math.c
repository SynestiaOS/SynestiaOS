//
// Created by XingfengYang on 2020/7/12.
//
#include <math.h>

float fmod(float x, float y) { return __builtin_fmod(x, y); }

float cosf(float x) { return __builtin_cosf(x); }

float sinf(float x) { return __builtin_sinf(x); }

float tanf(float angle) { __builtin_sinf(angle) / __builtin_cosf(angle); }

float fmax(float x, float y) { return x > y ? x : y; }

float powf(float x, float y) { return __builtin_powf(x, y); }
