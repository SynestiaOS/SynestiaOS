//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_window.h>
#include <gfx2d.h>

#define FLUENT_PRIMARY_COLOR 0x0078D4


void gui_window(GUIWindow *window, uint32_t x, uint32_t y, const char *title) {
    Position position;
    position.x = x;
    position.y = y;
    window->component.position = position;

    window->title = title;
    window->component.size.height = 200;

    char *tmp = title;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    window->component.size.width = 300;
    Color colorBg;
    colorBg.a = 0x00;
    colorBg.r = 0xFF;
    colorBg.g = 0xFF;
    colorBg.b = 0xFF;
    window->component.background = colorBg;


    Color colorFore;
    colorFore.a = 0x00;
    colorFore.r = 0xFF;
    colorFore.g = 0xFF;
    colorFore.b = 0xFF;
    window->component.foreground = colorFore;
}

void gui_draw_window(GUIWindow *window) {
    // 1. draw_background
    gfx2d_fill_rect(
            window->component.position.x,
            window->component.position.y,
            window->component.position.x + window->component.size.width,
            window->component.position.y + window->component.size.height + 24,
            window->component.background.r << 16 | window->component.background.g << 8 | window->component.background.b
    );

    // 2. draw header
    gfx2d_fill_rect(
            window->component.position.x,
            window->component.position.y,
            window->component.position.x + window->component.size.width,
            window->component.position.y + 24,
            FLUENT_PRIMARY_COLOR
    );

    // 3. draw_font
    char *tmp = window->title;
    uint32_t xOffset = 0;
    while (*tmp) {
        gfx2d_draw_ascii(
                window->component.position.x + xOffset * 8 + 8,
                window->component.position.y + 8,
                *tmp,
                window->component.foreground.r << 16 | window->component.foreground.g << 8 | window->component.foreground.b
        );
        xOffset++;
        tmp++;
    }

    // 4. draw header button
    gfx2d_fill_rect(
            window->component.position.x + window->component.size.width - 24 * 3,
            window->component.position.y + 4,
            window->component.position.x + window->component.size.width - 24 * 3 + 16,
            window->component.position.y + 4 + 16,
            0x00FFFFFF
    );
    gfx2d_draw_ascii(window->component.position.x + window->component.size.width - 24 * 3 + 4,
                   window->component.position.y + 4 + 4, '_', FLUENT_PRIMARY_COLOR);
    gfx2d_fill_rect(
            window->component.position.x + window->component.size.width - 24 * 2,
            window->component.position.y + 4,
            window->component.position.x + window->component.size.width - 24 * 2 + 16,
            window->component.position.y + 4 + 16,
            0x00FFFFFF
    );
    gfx2d_draw_ascii(window->component.position.x + window->component.size.width - 24 * 2 + 4,
                   window->component.position.y + 4 + 4, 'o', FLUENT_PRIMARY_COLOR);

    gfx2d_fill_rect(
            window->component.position.x + window->component.size.width - 24 * 1,
            window->component.position.y + 4,
            window->component.position.x + window->component.size.width - 24 * 1 + 16,
            window->component.position.y + 4 + 16,
            0x00FFFFFF
    );
    gfx2d_draw_ascii(window->component.position.x + window->component.size.width - 24 * 1 + 4,
                   window->component.position.y + 4 + 4, 'x', FLUENT_PRIMARY_COLOR);

    // 5. draw border
    gfx2d_draw_rect(
            window->component.position.x,
            window->component.position.y,
            window->component.position.x + window->component.size.width,
            window->component.position.y + window->component.size.height + 24,
            FLUENT_PRIMARY_COLOR
    );

    // 6. register click event

    // 7. register drag event
}
