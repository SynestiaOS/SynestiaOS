//
// Created by XingfengYang on 2020/7/7.
//

#include <stdint.h>

#ifndef __LIBRARY_LIBGFX_GL2D_H__
#define __LIBRARY_LIBGFX_GL2D_H__

#define FLUENT_PRIMARY_COLOR 0x880A0A0A
#define FLUENT_PRIMARY_BACK_COLOR 0x88191B1A
#define FLUENT_PRIMARY_FORE_COLOR 0xFFFFFF


typedef void (*Gfx2DContextOperationDrawPixelColor)(struct Gfx2DContext *context, uint32_t x, uint32_t y, uint32_t c);

typedef void (*Gfx2DContextOperationDrawPixel)(struct Gfx2DContext *context, int x, int y, uint32_t c);

typedef void (*Gfx2DContextOperationDrawRect)(struct Gfx2DContext *context, int x1, int y1, int x2, int y2, uint32_t c);

typedef void (*Gfx2DContextOperationFillRect)(struct Gfx2DContext *context, int x1, int y1, int x2, int y2, uint32_t c);

typedef void (*Gfx2DContextOperationDrawLine)(struct Gfx2DContext *context, int x1, int y1, int x2, int y2, uint32_t c);

typedef void (*Gfx2DContextOperationDrawTriangle)(struct Gfx2DContext *context, int x1, int y1, int x2, int y2, int x3,
                                                  int y3, uint32_t c);

typedef void (*Gfx2DContextOperationFillTriangle)(struct Gfx2DContext *context, int x1, int y1, int x2, int y2, int x3,
                                                  int y3, uint32_t c);

typedef void (*Gfx2DContextOperationDrawCircle)(struct Gfx2DContext *context, int xc, int yc, int r, uint32_t c);

typedef void (*Gfx2DContextOperationFillCircle)(struct Gfx2DContext *context, int xc, int yc, int r, uint32_t c);

typedef void (*Gfx2DContextOperationDrawAscii)(struct Gfx2DContext *context, int x, int y, uint8_t ch, uint32_t color);

typedef void (*Gfx2DContextOperationDrawBitmap)(struct Gfx2DContext *context, int x, int y, int width, int height,
                                                uint32_t *bitmap);

typedef struct Gfx2DContextOperations {
    Gfx2DContextOperationDrawPixel drawPixel;
    Gfx2DContextOperationDrawPixelColor drawPixeColor;
    Gfx2DContextOperationDrawRect drawRect;
    Gfx2DContextOperationFillRect fillRect;
    Gfx2DContextOperationDrawLine drawLine;
    Gfx2DContextOperationDrawTriangle drawTriangle;
    Gfx2DContextOperationFillTriangle fillTriangle;
    Gfx2DContextOperationDrawCircle drawCircle;
    Gfx2DContextOperationFillCircle fillCircle;
    Gfx2DContextOperationDrawAscii drawAscii;
    Gfx2DContextOperationDrawBitmap drawBitmap;
} Gfx2DContextOperations;
typedef struct Gfx2DContext {
    uint32_t width;
    uint32_t height;
    uint32_t *buffer;

    Gfx2DContextOperations operations;
} Gfx2DContext;

Gfx2DContext *gfx2d_create_context(Gfx2DContext *context, uint32_t width, uint32_t height, uint32_t *buffer);

#endif //__LIBRARY_LIBGFX_GL2D_H__
