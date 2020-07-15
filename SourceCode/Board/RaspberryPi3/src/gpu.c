//
// Created by XingfengYang on 2020/7/7.
//

#include <gpu.h>
#include <stdint.h>
#include <framebuffer.h>
#include <stdlib.h>
#include <interrupt.h>
#include <kheap.h>

void gpu_write_pixel(uint32_t x, uint32_t y, const pixel_t *pix) {
    framebuffer_draw_pixel(x, y, pix->red, pix->green, pix->blue);
}

unsigned char SCREEN_BUFFER[1024 * 768 * 4] = {'\0'};
extern uint32_t pitch;
extern unsigned char *lfb;

void gpu_write_pixel_color(uint32_t x, uint32_t y, uint32_t c) {
    uint32_t r = (c >> 16) & 0xFF;
    uint32_t g = (c >> 8) & 0xFF;
    uint32_t b = c & 0xFF;

    unsigned char *ptr = &SCREEN_BUFFER;

    ptr += pitch * y;
    ptr += (x << 2);

    uint32_t pixel = (b << 16) | (g << 8) | r;

    *((uint32_t *) ptr) = *(&pixel);
}

void gpu_flush() {
    printf("[GPU]: flush.\n");
    memcpy(lfb, &SCREEN_BUFFER, 1024 * 768 * 4);
}

TimerHandler timer;
void gpu_init(void) {
    framebuffer_init();
    printf("[Framebuffer]: Inited 1024x768x32\n");
    framebuffer_clear(0xFFFFFF);

    timer.node.next = nullptr;
    timer.node.prev = nullptr;
    timer.timer_interrupt_handler = &gpu_flush;

    register_time_interrupt(&timer);
}
