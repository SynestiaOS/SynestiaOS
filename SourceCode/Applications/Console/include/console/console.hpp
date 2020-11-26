//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __APPLICATIONS_CONSOLE_H__
#define __APPLICATIONS_CONSOLE_H__

#include "libc/stdint.hpp"

typedef struct Console {
    char *buffer;
    char *videoBuffer;
    uint32_t posX;
    uint32_t posY;

    uint32_t width;
    uint32_t height;

    uint32_t fontSize;
    uint32_t backgroundColor;
    uint32_t foregroundColor;
} Console;

void console_clear();

void console_printf();

#endif//__APPLICATIONS_CONSOLE_H__
