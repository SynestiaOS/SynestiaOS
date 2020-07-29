//
// Created by XingfengYang on 2020/7/14.
//

#ifndef __LIBRARY_LIBGUI_CANVAS_H__
#define __LIBRARY_LIBGUI_CANVAS_H__

#include <gui_component.h>

#define DEFAULT_CANVAS_WIDTH 200
#define DEFAULT_CANVAS_HEIGHT 150

typedef struct GUICanvas {
  GUIComponent component;
  uint32_t *buffer;
} GUICanvas;

void gui_canvas_create(GUICanvas *canvas);

void gui_canvas_init(GUICanvas *canvas, uint32_t x, uint32_t y);

void gui_canvas_draw_pixel(GUICanvas *canvas, int x, int y, uint32_t c);

void gui_canvas_draw_rect(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c);

void gui_canvas_fill_rect(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c);

void gui_canvas_draw_line(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c);

void gui_canvas_draw_triangle(GUICanvas *canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gui_canvas_fill_triangle(GUICanvas *canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);

void gui_canvas_draw_circle(GUICanvas *canvas, int xc, int yc, int r, uint32_t c);

void gui_canvas_fill_circle(GUICanvas *canvas, int xc, int yc, int r, uint32_t c);

void gui_canvas_draw_ascii(GUICanvas *canvas, int x, int y, uint8_t ch, uint32_t color);

void gui_canvas_draw_bitmap(GUICanvas *canvas, int x, int y, int width, int height, uint32_t *buffer);

void gui_canvas_clear(GUICanvas *canvas, uint32_t color);

void gui_canvas_draw(GUICanvas *canvas);

#endif //__LIBRARY_LIBGUI_CANVAS_H__
