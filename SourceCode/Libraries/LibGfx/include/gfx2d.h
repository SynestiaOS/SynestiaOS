//
// Created by XingfengYang on 2020/7/7.
//

#include <stdint.h>

#ifndef __LIBRARY_LIBGFX_GL2D_H__
#define __LIBRARY_LIBGFX_GL2D_H__

#define FLUENT_PRIMARY_COLOR 0x880A0A0A
#define FLUENT_PRIMARY_BACK_COLOR 0x88191B1A
#define FLUENT_PRIMARY_FORE_COLOR 0xFFFFFF

typedef struct Gfx2DContext {
    uint32_t width;
    uint32_t height;
    uint32_t* buffer;
} Gfx2DContext;

void gfx2d_draw_pixel(Gfx2DContext context, int x, int y, uint32_t c);

void gfx2d_draw_rect(Gfx2DContext context, int x1, int y1, int x2, int y2, uint32_t c);

void gfx2d_fill_rect(Gfx2DContext context, int x1, int y1, int x2, int y2, uint32_t c);

void gfx2d_draw_line(Gfx2DContext context, int x1, int y1, int x2, int y2, uint32_t c);

void gfx2d_draw_triangle(Gfx2DContext context, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gfx2d_fill_triangle(Gfx2DContext context, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gfx2d_draw_circle(Gfx2DContext context, int xc, int yc, int r, uint32_t c);

void gfx2d_fill_circle(Gfx2DContext context, int xc, int yc, int r, uint32_t c);

void gfx2d_draw_ascii(Gfx2DContext context, int x, int y, uint8_t ch, uint32_t color);

void gfx2d_draw_bitmap(Gfx2DContext context, int x, int y, int width, int height, uint32_t* bitmap);

#endif //__LIBRARY_LIBGFX_GL2D_H__
