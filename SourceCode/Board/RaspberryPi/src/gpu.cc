//
// Created by XingfengYang on 2020/7/7.
//

#include <kernel/log.h>
#include <libc/stdint.h>
#include <libc/stdlib.h>
#include <raspi2/framebuffer.h>
#include <raspi2/gpu.h>

extern uint32_t GFX2D_BUFFER[1024 * 768];

extern uint32_t pitch;
extern unsigned char *lfb;

void gpu_write_pixel_color(uint32_t x, uint32_t y, uint32_t c) {
    uint32_t r = (c >> 16) & 0xFF;
    uint32_t g = (c >> 8) & 0xFF;
    uint32_t b = c & 0xFF;

    unsigned char *ptr = lfb;

    ptr += pitch * y;
    ptr += (x << 2);

    uint32_t pixel = (b << 16) | (g << 8) | r;

    *((uint32_t *) ptr) = *(&pixel);
}

uint32_t *gpu_flush(int arg) {
    int index = 0;
    for (uint32_t i = 0; i < 768; i++) {
        for (uint32_t j = 0; j < 1024; j++) {
            gpu_write_pixel_color(j, i, GFX2D_BUFFER[index]);
            index++;
        }
    }
}

void gpu_init(void) {
    framebuffer_init();
    LogInfo("[Framebuffer]: Inited 1024x768x32\n");
    framebuffer_clear(0xFFFFFF);
}
