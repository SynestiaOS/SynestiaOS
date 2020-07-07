//
// Created by XingfengYang on 2020/7/7.
//

#include <gfx2d.h>
#include <stdbool.h>

void gpu_write_pixel_color(uint32_t x, uint32_t y, uint32_t c);

void gfx_fill(int x1, int y1, int x2, int y2, uint32_t c) {
    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            gpu_write_pixel_color(x, y, c);
        }
    }
}

void gfx_draw_line(int x1, int y1, int x2, int y2, uint32_t c) {
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;
    int dx1 = 0;
    int dy1 = 0;
    int px = 0;
    int py = 0;
    int xe = 0;
    int ye = 0;
    int i = 0;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = __builtin_abs(dx);
    dy1 = __builtin_abs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = x1;
            y = y1;
            xe = x2;
        } else {
            x = x2;
            y = y2;
            xe = x1;
        }

        gpu_write_pixel_color(x, y, c);

        for (i = 0; x < xe; i++) {
            x = x + 1;
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            gpu_write_pixel_color(x, y, c);
        }
    } else {
        if (dy >= 0) {
            x = x1;
            y = y1;
            ye = y2;
        } else {
            x = x2;
            y = y2;
            ye = y1;
        }
        gpu_write_pixel_color(x, y, c);
        for (i = 0; y < ye; i++) {
            y = y + 1;
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            gpu_write_pixel_color(x, y, c);
        }
    }
}


void gfx_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    gfx_draw_line(x1, y1, x2, y2, c);
    gfx_draw_line(x2, y2, x3, y3, c);
    gfx_draw_line(x3, y3, x1, y1, c);
}

void drawline(int sx, int ex, int ny, int c) {
    for (int i = sx; i <= ex; i++) {
        gpu_write_pixel_color(i, ny, c);
    }
}

void gfx_fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {

}


void gfx_draw_circle(int xc, int yc, int r, uint32_t c) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) { return; };

    while (y >= x) { // only formulate 1/8 of circle
        gpu_write_pixel_color(xc - x, yc - y, c);//upper left left
        gpu_write_pixel_color(xc - y, yc - x, c);//upper upper left
        gpu_write_pixel_color(xc + y, yc - x, c);//upper upper right
        gpu_write_pixel_color(xc + x, yc - y, c);//upper right right
        gpu_write_pixel_color(xc - x, yc + y, c);//lower left left
        gpu_write_pixel_color(xc - y, yc + x, c);//lower lower left
        gpu_write_pixel_color(xc + y, yc + x, c);//lower lower right
        gpu_write_pixel_color(xc + x, yc + y, c);//lower right right
        if (p < 0) {
            p += 4 * x++ + 6;
        } else {
            p += 4 * (x++ - y--) + 10;
        }
    }
}

void gfx_fill_circle(int xc, int yc, int r, uint32_t c) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) { return; };

    while (y >= x) {
        // Modified to draw scan-lines instead of edges
        drawline(xc - x, xc + x, yc - y, c);
        drawline(xc - y, xc + y, yc - x, c);
        drawline(xc - x, xc + x, yc + y, c);
        drawline(xc - y, xc + y, yc + x, c);
        if (p < 0) {
            p += 4 * x++ + 6;
        } else {
            p += 4 * (x++ - y--) + 10;
        }
    }
}

