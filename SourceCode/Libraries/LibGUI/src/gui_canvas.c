//
// Created by XingfengYang on 2020/7/14.
//

#include "libgui/gui_canvas.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "libgfx/gfx2d.h"

extern Heap kernelHeap;

extern uint32_t GFX2D_BUFFER[1024 * 768];

void gui_canvas_create(GUICanvas *canvas) {
    canvas->component.type = CANVAS;
    canvas->component.visable = true;
    canvas->component.colorMode = RGB;

    canvas->component.node.next = nullptr;
    canvas->component.node.prev = nullptr;

    canvas->component.position.x = 0;
    canvas->component.position.y = 0;

    canvas->component.size.height = DEFAULT_CANVAS_HEIGHT;
    canvas->component.size.width = DEFAULT_CANVAS_WIDTH;

    canvas->component.padding.top = DEFAULT_PADDING;
    canvas->component.padding.bottom = DEFAULT_PADDING;
    canvas->component.padding.left = DEFAULT_PADDING;
    canvas->component.padding.right = DEFAULT_PADDING;
    canvas->component.margin.top = DEFAULT_MARGIN;
    canvas->component.margin.bottom = DEFAULT_MARGIN;
    canvas->component.margin.left = DEFAULT_MARGIN;
    canvas->component.margin.right = DEFAULT_MARGIN;

    canvas->component.background.a = 0x00;
    canvas->component.background.r = 0xFF;
    canvas->component.background.g = 0xFF;
    canvas->component.background.b = 0xFF;
    canvas->component.foreground.a = 0x00;
    canvas->component.foreground.r = 0x00;
    canvas->component.foreground.g = 0x00;
    canvas->component.foreground.b = 0x00;

    canvas->buffer = (unsigned char *) kernelHeap.operations.alloc(&kernelHeap, canvas->component.size.width *
                                                                                        canvas->component.size.height * 4);
    if (canvas->buffer == nullptr) {
        LogError("[GUI]: canvas create failed, unable to allocate buffer memory\n");
    }

    gfx2d_create_surface(&canvas->surface, canvas->component.size.width, canvas->component.size.height, canvas->buffer);
}

void gui_canvas_init(GUICanvas *canvas, uint32_t x, uint32_t y) {
    canvas->component.position.x = x;
    canvas->component.position.y = y;
}

void gui_canvas_draw_pixel(GUICanvas *canvas, int x, int y, uint32_t c) {
    if (x >= canvas->component.size.width || x < 0) {
        return;
    }

    if (y >= canvas->component.size.height || y < 0) {
        return;
    }

    canvas->surface.operations.drawPixel(&canvas->surface, canvas->component.position.x + x,
                                         canvas->component.position.y + y, c);
}

void gui_canvas_draw_rect(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c) {
    canvas->surface.operations.drawRect(&canvas->surface, canvas->component.position.x + x1,
                                        canvas->component.position.y + y1,
                                        canvas->component.position.x + x2, canvas->component.position.y + y2, c);
}

void gui_canvas_fill_rect(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c) {
    canvas->surface.operations.fillRect(&canvas->surface, canvas->component.position.x + x1,
                                        canvas->component.position.y + y1,
                                        canvas->component.position.x + x2, canvas->component.position.y + y2, c);
}

void gui_canvas_draw_line(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c) {
    canvas->surface.operations.drawLine(&canvas->surface, canvas->component.position.x + x1,
                                        canvas->component.position.y + y1,
                                        canvas->component.position.x + x2, canvas->component.position.y + y2, c);
}

void gui_canvas_draw_triangle(GUICanvas *canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    canvas->surface.operations.drawTriangle(&canvas->surface, canvas->component.position.x + x1,
                                            canvas->component.position.y + y1,
                                            canvas->component.position.x + x2, canvas->component.position.y + y2,
                                            canvas->component.position.x + x3, canvas->component.position.y + y3, c);
}

void gui_canvas_fill_triangle(GUICanvas *canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    canvas->surface.operations.fillTriangle(&canvas->surface, canvas->component.position.x + x1,
                                            canvas->component.position.y + y1,
                                            canvas->component.position.x + x2, canvas->component.position.y + y2,
                                            canvas->component.position.x + x3, canvas->component.position.y + y3, c);
}

void gui_canvas_draw_circle(GUICanvas *canvas, int xc, int yc, int r, uint32_t c) {
    canvas->surface.operations.drawCircle(&canvas->surface, canvas->component.position.x + xc,
                                          canvas->component.position.y + yc, r, c);
}

void gui_canvas_fill_circle(GUICanvas *canvas, int xc, int yc, int r, uint32_t c) {
    canvas->surface.operations.fillCircle(&canvas->surface, canvas->component.position.x + xc,
                                          canvas->component.position.y + yc, r, c);
}

void gui_canvas_draw_ascii(GUICanvas *canvas, int x, int y, uint8_t ch, uint32_t color) {
    canvas->surface.operations.drawAscii(&canvas->surface, canvas->component.position.x + x,
                                         canvas->component.position.y + y, ch, color);
}

void gui_canvas_draw_bitmap(GUICanvas *canvas, int x, int y, int width, int height, uint32_t *buffer) {
    canvas->surface.operations.drawBitmap(&canvas->surface, canvas->component.position.x + x,
                                          canvas->component.position.y + y, width, height, buffer);
}

void gui_canvas_clear(GUICanvas *canvas, uint32_t color) {
    canvas->surface.operations.fillRect(&canvas->surface, 0, 0, canvas->component.size.width,
                                        canvas->component.size.height, color);
}

void gui_canvas_draw(GUICanvas *canvas) {
    GfxSurface surface = {.width = 1024, .height = 768, .buffer = GFX2D_BUFFER};
    canvas->surface.operations.drawBitmap(&surface, canvas->component.position.x, canvas->component.position.y,
                                          canvas->component.size.width,
                                          canvas->component.size.height, canvas->surface.buffer);
}
