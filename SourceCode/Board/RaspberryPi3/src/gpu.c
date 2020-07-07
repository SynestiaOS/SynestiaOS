//
// Created by XingfengYang on 2020/7/7.
//

#include <gpu.h>
#include <stdint.h>
#include <framebuffer.h>
#include <stdlib.h>

void gpu_write_pixel(uint32_t x, uint32_t y, const pixel_t *pix) {
    framebuffer_draw_pixel(x, y, pix->red, pix->green, pix->blue);
}

void gpu_write_pixel_color(uint32_t x, uint32_t y, uint32_t c) {
    framebuffer_draw_pixel(x, y, (c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
}

void gpu_init(void) {
    framebuffer_init();
    printf("[Framebuffer] Inited: 1024x768x32\n");
    framebuffer_clear(0x000000);
}
