//
// Created by XingfengYang on 2020/7/7.
//

#include <libgfx/font8bits.h>
#include <libgfx/gfx2d.h>

uint32_t GFX2D_BUFFER[1024 * 768] = {0xFF};

void gfx2d_default_write_pixel_color(Gfx2DContext *context, uint32_t x, uint32_t y, uint32_t c) {

    uint32_t color = c;
    uint32_t alpha = (color >> 24) & 0xFF;
    uint32_t r = (color >> 16) & 0xFF;
    uint32_t g = (color >> 8) & 0xFF;
    uint32_t b = (color) &0xFF;

    uint32_t backColor = context->buffer[y * context->width + x];
    uint32_t backR = (backColor >> 16) & 0xFF;
    uint32_t backG = (backColor >> 8) & 0xFF;
    uint32_t backB = (backColor) &0xFF;

    uint32_t mixedR = ((0xFF - alpha) * r) / 0xFF + (alpha * backR) / 0xFF;
    uint32_t mixedG = ((0xFF - alpha) * g) / 0xFF + (alpha * backG) / 0xFF;
    uint32_t mixedB = ((0xFF - alpha) * b) / 0xFF + (alpha * backB) / 0xFF;

    context->buffer[y * context->width + x] = mixedR << 16 | mixedG << 8 | mixedB;
}

void gfx2d_default_draw_pixel(Gfx2DContext *context, int x, int y, uint32_t c) {
    gfx2d_default_write_pixel_color(context, x, y, c);
}


void gfx2d_default_draw_line(Gfx2DContext *context, int x1, int y1, int x2, int y2, uint32_t c) {
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

        gfx2d_default_write_pixel_color(context, x, y, c);

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
            gfx2d_default_write_pixel_color(context, x, y, c);
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
        gfx2d_default_write_pixel_color(context, x, y, c);
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
            gfx2d_default_write_pixel_color(context, x, y, c);
        }
    }
}

void gfx2d_default_draw_rect(Gfx2DContext *context, int x1, int y1, int x2, int y2, uint32_t c) {
    gfx2d_default_draw_line(context, x1, y1, x1, y2, c);
    gfx2d_default_draw_line(context, x1, y1, x2, y1, c);
    gfx2d_default_draw_line(context, x2, y1, x2, y2, c);
    gfx2d_default_draw_line(context, x1, y2, x2, y2, c);
}

void gfx2d_default_fill_rect(Gfx2DContext *context, int x1, int y1, int x2, int y2, uint32_t c) {
    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            gfx2d_default_write_pixel_color(context, x, y, c);
        }
    }
}

void gfx2d_default_draw_triangle(Gfx2DContext *context, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    gfx2d_default_draw_line(context, x1, y1, x2, y2, c);
    gfx2d_default_draw_line(context, x2, y2, x3, y3, c);
    gfx2d_default_draw_line(context, x3, y3, x1, y1, c);
}

void drawline(Gfx2DContext *context, int sx, int ex, int ny, int c) {
    for (int i = sx; i <= ex; i++) {
        gfx2d_default_write_pixel_color(context, i, ny, c);
    }
}

void SWAP(int *x, int *y) {
    int temp = 0;

    temp = *x;
    *x = *y;
    *y = temp;
}

void gfx2d_default_fill_triangle(Gfx2DContext *context, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c) {
    int t1x = 0;
    int t2x = 0;
    int y = 0;
    int minx = 0;
    int maxx = 0;
    int t1xp = 0;
    int t2xp = 0;
    bool changed1 = false;
    bool changed2 = false;
    int signx1 = 0;
    int signx2 = 0;
    int dx1 = 0;
    int dy1 = 0;
    int dx2 = 0;
    int dy2 = 0;
    int e1 = 0;
    int e2 = 0;
    // Sort vertices
    if (y1 > y2) {
        SWAP(&y1, &y2);
        SWAP(&x1, &x2);
    }
    if (y1 > y3) {
        SWAP(&y1, &y3);
        SWAP(&x1, &x3);
    }
    if (y2 > y3) {
        SWAP(&y2, &y3);
        SWAP(&x2, &x3);
    }

    t1x = t2x = x1;
    y = y1;// Starting points
    dx1 = (x2 - x1);
    if (dx1 < 0) {
        dx1 = -dx1;
        signx1 = -1;
    } else {
        signx1 = 1;
    }
    dy1 = (y2 - y1);

    dx2 = (x3 - x1);
    if (dx2 < 0) {
        dx2 = -dx2;
        signx2 = -1;
    } else {
        signx2 = 1;
    }
    dy2 = (y3 - y1);

    if (dy1 > dx1) {// swap values
        SWAP(&dx1, &dy1);
        changed1 = true;
    }
    if (dy2 > dx2) {// swap values
        SWAP(&dy2, &dx2);
        changed2 = true;
    }

    e2 = (dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2) {
        goto next;
    }
    e1 = (dx1 >> 1);

    for (int i = 0; i < dx1;) {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x) {
            minx = t1x;
            maxx = t2x;
        } else {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1) {
            i++;
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) {
                    t1xp = signx1;// t1x += signx1;
                } else {
                    goto next1;
                }
            }
            if (changed1) {
                break;
            }
            t1x += signx1;
        }
    // Move line
    next1:
        // process second line until y value is about to change
        while (1) {
            e2 += dy2;
            while (e2 >= dx2) {
                e2 -= dx2;
                if (changed2) {
                    t2xp = signx2;// t2x += signx2;
                } else {
                    goto next2;
                }
            }
            if (changed2) {
                break;
            }
            t2x += signx2;
        }
    next2:
        if (minx > t1x) {
            minx = t1x;
        }
        if (minx > t2x) {
            minx = t2x;
        }
        if (maxx < t1x) {
            maxx = t1x;
        }
        if (maxx < t2x) {
            maxx = t2x;
        }
        drawline(context, minx, maxx, y, c);// Draw line from min to max points found on the y
        // Now increase y
        if (!changed1) {
            t1x += signx1;
        }
        t1x += t1xp;
        if (!changed2) {
            t2x += signx2;
        }
        t2x += t2xp;
        y += 1;
        if (y == y2) {
            break;
        }
    }
next:
    // Second half
    dx1 = (x3 - x2);
    if (dx1 < 0) {
        dx1 = -dx1;
        signx1 = -1;
    } else {
        signx1 = 1;
    }
    dy1 = (y3 - y2);
    t1x = x2;

    if (dy1 > dx1) {// swap values
        SWAP(&dy1, &dx1);
        changed1 = true;
    } else {
        changed1 = false;
    }

    e1 = (dx1 >> 1);

    for (int i = 0; i <= dx1; i++) {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x) {
            minx = t1x;
            maxx = t2x;
        } else {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1) {
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) {
                    t1xp = signx1;
                    break;
                }// t1x += signx1;
                goto next3;
            }
            if (changed1) {
                break;
            }
            t1x += signx1;
            if (i < dx1) {
                i++;
            }
        }
    next3:
        // process second line until y value is about to change
        while (t2x != x3) {
            e2 += dy2;
            while (e2 >= dx2) {
                e2 -= dx2;
                if (changed2) {
                    t2xp = signx2;
                } else {
                    goto next4;
                }
            }
            if (changed2) {
                break;
            }
            t2x += signx2;
        }
    next4:

        if (minx > t1x) {
            minx = t1x;
        }
        if (minx > t2x) {
            minx = t2x;
        }
        if (maxx < t1x) {
            maxx = t1x;
        }
        if (maxx < t2x) {
            maxx = t2x;
        }
        drawline(context, minx, maxx, y, c);
        if (!changed1) {
            t1x += signx1;
        }
        t1x += t1xp;
        if (!changed2) {
            t2x += signx2;
        }
        t2x += t2xp;
        y += 1;
        if (y > y3) {
            return;
        }
    }
}

void gfx2d_default_draw_circle(Gfx2DContext *context, int xc, int yc, int r, uint32_t c) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) {
        return;
    }

    while (y >= x) {                                                // only formulate 1/8 of circle
        gfx2d_default_write_pixel_color(context, xc - x, yc - y, c);// upper left left
        gfx2d_default_write_pixel_color(context, xc - y, yc - x, c);// upper upper left
        gfx2d_default_write_pixel_color(context, xc + y, yc - x, c);// upper upper right
        gfx2d_default_write_pixel_color(context, xc + x, yc - y, c);// upper right right
        gfx2d_default_write_pixel_color(context, xc - x, yc + y, c);// lower left left
        gfx2d_default_write_pixel_color(context, xc - y, yc + x, c);// lower lower left
        gfx2d_default_write_pixel_color(context, xc + y, yc + x, c);// lower lower right
        gfx2d_default_write_pixel_color(context, xc + x, yc + y, c);// lower right right
        if (p < 0) {
            p += 4 * x++ + 6;
        } else {
            p += 4 * (x++ - y--) + 10;
        }
    }
}

void gfx2d_default_fill_circle(Gfx2DContext *context, int xc, int yc, int r, uint32_t c) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) {
        return;
    }

    while (y >= x) {
        // Modified to draw scan-lines instead of edges
        drawline(context, xc - x, xc + x, yc - y, c);
        drawline(context, xc - y, xc + y, yc - x, c);
        drawline(context, xc - x, xc + x, yc + y, c);
        drawline(context, xc - y, xc + y, yc + x, c);
        if (p < 0) {
            p += 4 * x++ + 6;
        } else {
            p += 4 * (x++ - y--) + 10;
        }
    }
}

void gfx2d_default_draw_ascii(Gfx2DContext *context, int x, int y, uint8_t ch, uint32_t color) {
    uint8_t *bitmap = font_8_bits(ch);
    for (uint32_t i = 0; i < 8; i++) {
        for (uint32_t j = 0; j < 8; j++) {
            if ((bitmap[i] & (0x1 << j)) > 0) {
                gfx2d_default_write_pixel_color(context, x + j, y + i, color);
            }
        }
    }
}

void gfx2d_default_draw_bitmap(Gfx2DContext *context, int x, int y, int width, int height, uint32_t *bitmap) {
    int index = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = width; j > 0; j--) {
            uint32_t color = bitmap[index];
            gfx2d_default_write_pixel_color(context, x + j, y + i, color);
            index++;
        }
    }
}

Gfx2DContext *gfx2d_create_context(Gfx2DContext *context, uint32_t width, uint32_t height, uint32_t *buffer) {

    context->buffer = buffer;
    context->height = height;
    context->width = width;

    context->operations.drawPixel = gfx2d_default_draw_pixel;
    context->operations.drawPixeColor = gfx2d_default_write_pixel_color;
    context->operations.drawRect = gfx2d_default_draw_rect;
    context->operations.fillRect = gfx2d_default_fill_rect;
    context->operations.drawLine = gfx2d_default_draw_line;
    context->operations.drawTriangle = gfx2d_default_draw_triangle;
    context->operations.fillTriangle = gfx2d_default_fill_triangle;
    context->operations.drawCircle = gfx2d_default_draw_circle;
    context->operations.fillCircle = gfx2d_default_fill_circle;
    context->operations.drawAscii = gfx2d_default_draw_ascii;
    context->operations.drawBitmap = gfx2d_default_draw_bitmap;
}
