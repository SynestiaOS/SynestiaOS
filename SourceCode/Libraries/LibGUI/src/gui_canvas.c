//
// Created by XingfengYang on 2020/7/14.
//

#include <gui_canvas.h>
#include <stdbool.h>
#include <kheap.h>
#include <stdlib.h>
#include <gfx2d.h>

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

    canvas->buffer = kheap_alloc(canvas->component.size.width * canvas->component.size.height * sizeof(uint32_t));
    if (canvas->buffer == nullptr) {
        printf("[GUI]: canvas create failed, unable to allocate buffer memory\n");
    }
}

void gui_canvas_init(GUICanvas *canvas, uint32_t x, uint32_t y) {
    canvas->component.position.x = x;
    canvas->component.position.y = y;
}

void gui_canvas_draw_pixel(GUICanvas *canvas, int x, int y, uint32_t c) {
    if (x > canvas->component.size.width || x < 0) {
        return;
    }

    if (y > canvas->component.size.height || y < 0) {
        return;
    }

    gfx2d_draw_pixel(canvas->component.position.x+x,canvas->component.position.y+y,c);
}

void gui_canvas_draw_rect(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c) {
    gfx2d_draw_rect(canvas->component.position.x+x1,canvas->component.position.y+y1,canvas->component.position.x+x2,canvas->component.position.y+y2,c);
}

void gui_canvas_fill_rect(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c) {
    gfx2d_fill_rect(canvas->component.position.x+x1,canvas->component.position.y+y1,canvas->component.position.x+x2,canvas->component.position.y+y2,c);
}

void gui_canvas_draw_line(GUICanvas *canvas, int x1, int y1, int x2, int y2, uint32_t c) {
    gfx2d_draw_line(canvas->component.position.x+x1,canvas->component.position.y+y1,canvas->component.position.x+x2,canvas->component.position.y+y2,c);
}

void gui_canvas_draw_triangle(GUICanvas *canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    gfx2d_draw_triangle(canvas->component.position.x+x1,canvas->component.position.y+y1,canvas->component.position.x+x2,canvas->component.position.y+y2,canvas->component.position.x+x3,canvas->component.position.y+y3,c);
}

void gui_canvas_fill_triangle(GUICanvas *canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    gfx2d_fill_triangle(canvas->component.position.x+x1,canvas->component.position.y+y1,canvas->component.position.x+x2,canvas->component.position.y+y2,canvas->component.position.x+x3,canvas->component.position.y+y3,c);
}

void gui_canvas_draw_circle(GUICanvas *canvas, int xc, int yc, int r, uint32_t c) {
    gfx2d_draw_circle(canvas->component.position.x+xc,canvas->component.position.y+yc,r,c);
}

void gui_canvas_fill_circle(GUICanvas *canvas, int xc, int yc, int r, uint32_t c) {
    gfx2d_fill_circle(canvas->component.position.x+xc,canvas->component.position.y+yc,r,c);
}

void gui_canvas_draw_ascii(GUICanvas *canvas, int x, int y, uint8_t ch, uint32_t color) {
    gfx2d_draw_ascii(canvas->component.position.x+x,canvas->component.position.y+y,ch,color);
}

void gui_canvas_draw_bitmap(GUICanvas *canvas, int x, int y, int width, int height, uint32_t *buffer) {
    gfx2d_draw_bitmap(canvas->component.position.x+x,canvas->component.position.y+y,width,height,buffer);
}

void gui_canvas_clear(GUICanvas *canvas,uint32_t color){

}

void gui_canvas_draw(GUICanvas *canvas) {

}
