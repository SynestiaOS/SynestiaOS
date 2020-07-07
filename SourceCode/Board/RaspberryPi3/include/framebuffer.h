//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP3_FRAMEBUFFER_H__
#define __BOARD_RASP3_FRAMEBUFFER_H__

#include <stdint.h>

#define COLORDEPTH 24
#define BYTES_PER_PIXEL COLORDEPTH/8

typedef struct framebuffer_info {
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    void *buf;
    uint32_t buf_size;
    uint32_t chars_width;
    uint32_t chars_height;
    uint32_t chars_x;
    uint32_t chars_y;
} framebuffer_info_t;

framebuffer_info_t fbinfo;

int framebuffer_init(void);

#endif //__BOARD_RASP3_FRAMEBUFFER_H__
