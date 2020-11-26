//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP_GPU_H__
#define __BOARD_RASP_GPU_H__

#include "libc/stdint.hpp"

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

void gpu_init(void);

void gpu_write_pixel_color(uint32_t x, uint32_t y, uint32_t color);

#endif//__BOARD_RASP_GPU_H__
