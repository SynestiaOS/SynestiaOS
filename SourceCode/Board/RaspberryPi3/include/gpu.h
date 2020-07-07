//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP3_GPU_H__
#define __BOARD_RASP3_GPU_H__

#include <stdint.h>

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

typedef struct pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

void gpu_init(void);

void gpu_write_pixel(uint32_t x, uint32_t y, const pixel_t *pixel);

void gpu_write_pixel_color(uint32_t x, uint32_t y, uint32_t color);

void gpu_putc(char c);

#endif //__BOARD_RASP3_GPU_H__
