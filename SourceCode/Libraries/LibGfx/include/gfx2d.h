//
// Created by XingfengYang on 2020/7/7.
//

#include <stdint.h>

#ifndef __LIBRARY_LIBGFX_GL2D_H__
#define __LIBRARY_LIBGFX_GL2D_H__

void gfx_fill(int x1, int y1, int x2, int y2, uint32_t c);

void gfx_draw_line(int x1, int y1, int x2, int y2, uint32_t c);

void gfx_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
void gfx_fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gfx_draw_circle(int xc, int yc, int r, uint32_t c);
void gfx_fill_circle(int xc, int yc, int r, uint32_t c);

#endif //__LIBRARY_LIBGFX_GL2D_H__
