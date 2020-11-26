//
// Created by Shifu Wu on 2020/11/25.
//

#pragma once

#ifdef __GNUC__

#define va_start(v, l)    __builtin_va_start(v,l)
#define va_end(v)    __builtin_va_end(v)
#define va_arg(v, l)    __builtin_va_arg(v,l)

typedef __builtin_va_list va_list;

#else
#error "currently only gcc(g++) is supported, define your implementation of stdarg.h here"
#endif
