//
// Created by XingfengYang on 2020/7/7.
//

#include <stdint.h>

#ifndef __LIBRARY_LIBGFX_GL2D_H__
#define __LIBRARY_LIBGFX_GL2D_H__


#define FLUENT_PRIMARY_COLOR 0x0078D4
//#define FLUENT_PRIMARY_COLOR 0xB3ADB2

void gfx2d_draw_rect(int x1, int y1, int x2, int y2, uint32_t c);

void gfx2d_fill_rect(int x1, int y1, int x2, int y2, uint32_t c);

void gfx2d_draw_line(int x1, int y1, int x2, int y2, uint32_t c);

void gfx2d_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gfx2d_fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gfx2d_draw_circle(int xc, int yc, int r, uint32_t c);

void gfx2d_fill_circle(int xc, int yc, int r, uint32_t c);

void gfx2d_draw_ascii(int x, int y, uint8_t ch, uint32_t color);

void gfx2d_draw_bitmap(int x, int y, int width, int height, uint32_t *buffer);

void gfx2d_draw_logo(int x, int y, uint32_t c);

#endif //__LIBRARY_LIBGFX_GL2D_H__
