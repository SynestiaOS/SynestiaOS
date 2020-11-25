//
// Created by XingfengYang on 2020/7/7.
//
#ifndef __BOARD_RASP_FRAMEBUFFER_H__
#define __BOARD_RASP_FRAMEBUFFER_H__

#include <libc/stdint.h>

uint32_t framebuffer_init(void);

void framebuffer_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b);

void framebuffer_clear(uint32_t color);

#endif//__BOARD_RASP_FRAMEBUFFER_H__
