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
    window->conponent.position = position;

    window->title = title;
    window->conponent.size.height = 200;

    char *tmp = title;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    window->conponent.size.width = 300;
    Color colorBg;
    colorBg.a = 0x00;
    colorBg.r = 0xFF;
    colorBg.g = 0xFF;
    colorBg.b = 0xFF;
    window->conponent.background = colorBg;


    Color colorFore;
    colorFore.a = 0x00;
    colorFore.r = 0xFF;
    colorFore.g = 0xFF;
    colorFore.b = 0xFF;
    window->conponent.foreground = colorFore;
}

void gui_draw_window(GUIWindow *window) {
    // 1. draw_background
    gfx_fill_rect(
            window->conponent.position.x,
            window->conponent.position.y,
            window->conponent.position.x + window->conponent.size.width,
            window->conponent.position.y + window->conponent.size.height + 24,
            window->conponent.background.r << 16 | window->conponent.background.g << 8 | window->conponent.background.b
    );

    // 2. draw header
    gfx_fill_rect(
            window->conponent.position.x,
            window->conponent.position.y,
            window->conponent.position.x + window->conponent.size.width,
            window->conponent.position.y + 24,
            FLUENT_PRIMARY_COLOR
    );

    // 3. draw_font
    char *tmp = window->title;
    uint32_t xOffset = 0;
    while (*tmp) {
        gfx_draw_ascii(
                window->conponent.position.x + xOffset * 8 + 8,
                window->conponent.position.y + 8,
                *tmp,
                window->conponent.foreground.r << 16 | window->conponent.foreground.g << 8 | window->conponent.foreground.b
        );
        xOffset++;
        tmp++;
    }

    // 4. draw header button
    gfx_fill_rect(
            window->conponent.position.x + window->conponent.size.width - 24 * 3,
            window->conponent.position.y + 4,
            window->conponent.position.x + window->conponent.size.width - 24 * 3 + 16,
            window->conponent.position.y + 4 + 16,
            0x00FFFFFF
    );
    gfx_draw_ascii(window->conponent.position.x + window->conponent.size.width - 24 * 3 + 4,
                   window->conponent.position.y + 4 + 4, '_', FLUENT_PRIMARY_COLOR);
    gfx_fill_rect(
            window->conponent.position.x + window->conponent.size.width - 24 * 2,
            window->conponent.position.y + 4,
            window->conponent.position.x + window->conponent.size.width - 24 * 2 + 16,
            window->conponent.position.y + 4 + 16,
            0x00FFFFFF
    );
    gfx_draw_ascii(window->conponent.position.x + window->conponent.size.width - 24 * 2 + 4,
                   window->conponent.position.y + 4 + 4, 'o', FLUENT_PRIMARY_COLOR);

    gfx_fill_rect(
            window->conponent.position.x + window->conponent.size.width - 24 * 1,
            window->conponent.position.y + 4,
            window->conponent.position.x + window->conponent.size.width - 24 * 1 + 16,
            window->conponent.position.y + 4 + 16,
            0x00FFFFFF
    );
    gfx_draw_ascii(window->conponent.position.x + window->conponent.size.width - 24 * 1 + 4,
                   window->conponent.position.y + 4 + 4, 'x', FLUENT_PRIMARY_COLOR);

    // 5. draw border
    gfx_draw_rect(
            window->conponent.position.x,
            window->conponent.position.y,
            window->conponent.position.x + window->conponent.size.width,
            window->conponent.position.y + window->conponent.size.height + 24,
            FLUENT_PRIMARY_COLOR
    );

    // 6. register click event

    // 7. register drag event
}
