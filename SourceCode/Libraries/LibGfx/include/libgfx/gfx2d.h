//
// Created by XingfengYang on 2020/7/7.
//

#include "libc/stdint.h"

#ifndef __LIBRARY_LIBGFX_GL2D_H__
#define __LIBRARY_LIBGFX_GL2D_H__

#define FLUENT_PRIMARY_COLOR 0x550A0A0A
#define FLUENT_PRIMARY_BACK_COLOR 0x88191B1A
#define FLUENT_PRIMARY_FORE_COLOR 0xFFFFFF


typedef void (*GfxSurfaceOperationDrawPixelColor)(struct GfxSurface *surface, uint32_t x, uint32_t y, uint32_t c);

typedef void (*GfxSurfaceOperationDrawPixel)(struct GfxSurface *surface, int x, int y, uint32_t c);

typedef void (*GfxSurfaceOperationDrawRect)(struct GfxSurface *surface, int x1, int y1, int x2, int y2, uint32_t c);

typedef void (*GfxSurfaceOperationFillRect)(struct GfxSurface *surface, int x1, int y1, int x2, int y2, uint32_t c);

typedef void (*GfxSurfaceOperationDrawLine)(struct GfxSurface *surface, int x1, int y1, int x2, int y2, uint32_t c);

typedef void (*GfxSurfaceOperationDrawTriangle)(struct GfxSurface *surface, int x1, int y1, int x2, int y2, int x3,
                                                  int y3, uint32_t c);

typedef void (*GfxSurfaceOperationFillTriangle)(struct GfxSurface *surface, int x1, int y1, int x2, int y2, int x3,
                                                  int y3, uint32_t c);

typedef void (*GfxSurfaceOperationDrawCircle)(struct GfxSurface *surface, int xc, int yc, int r, uint32_t c);

typedef void (*GfxSurfaceOperationFillCircle)(struct GfxSurface *surface, int xc, int yc, int r, uint32_t c);

typedef void (*GfxSurfaceOperationDrawAscii)(struct GfxSurface *surface, int x, int y, uint8_t ch, uint32_t color);

typedef void (*GfxSurfaceOperationDrawBitmap)(struct GfxSurface *surface, int x, int y, int width, int height,
                                                uint32_t *bitmap);

typedef struct GfxSurfaceOperations {
    GfxSurfaceOperationDrawPixel drawPixel;
    GfxSurfaceOperationDrawPixelColor drawPixelColor;
    GfxSurfaceOperationDrawRect drawRect;
    GfxSurfaceOperationFillRect fillRect;
    GfxSurfaceOperationDrawLine drawLine;
    GfxSurfaceOperationDrawTriangle drawTriangle;
    GfxSurfaceOperationFillTriangle fillTriangle;
    GfxSurfaceOperationDrawCircle drawCircle;
    GfxSurfaceOperationFillCircle fillCircle;
    GfxSurfaceOperationDrawAscii drawAscii;
    GfxSurfaceOperationDrawBitmap drawBitmap;
} GfxSurfaceOperations;

typedef struct GfxSurface {
    uint32_t width;
    uint32_t height;
    GfxSurfaceOperations operations;
    uint32_t *buffer;
} GfxSurface;

GfxSurface *gfx2d_create_surface(GfxSurface *surface, uint32_t width, uint32_t height, uint32_t *buffer);

#endif//__LIBRARY_LIBGFX_GL2D_H__
