//
// Created by XingfengYang on 2020/7/7.
//
#include <gui_button.h>
#include <gfx2d.h>

void gui_button(GUIButton *button, uint32_t x, uint32_t y, const char *text) {
    Position position;
    position.x = x;
    position.y = y;
    button->conponent.position = position;

    button->text = text;
    button->conponent.size.height = 16;

    char *tmp = text;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    button->conponent.size.width = length * 8 + 8;
    Color colorBg;
    colorBg.a = 0x00;
    colorBg.r = 0xA9;
    colorBg.g = 0xA9;
    colorBg.b = 0xA9;
    button->conponent.background = colorBg;


    Color colorFore;
    colorFore.a = 0x00;
    colorFore.r = 0x00;
    colorFore.g = 0x00;
    colorFore.b = 0x00;
    button->conponent.foreground = colorFore;
}

void gui_draw_button(GUIButton *button) {
    // 1. draw_background
    gfx_fill(
            button->conponent.position.x,
            button->conponent.position.y,
            button->conponent.position.x + button->conponent.size.width,
            button->conponent.position.y + button->conponent.size.height,
            button->conponent.background.r << 16 | button->conponent.background.g << 8 | button->conponent.background.b
    );

    // 2. draw_font
    char *tmp = button->text;
    uint32_t xOffset = 0;
    while (*tmp) {
        gfx_draw_ascii(
                button->conponent.position.x + xOffset * 8 + 4,
                button->conponent.position.y + 4,
                *tmp,
                button->conponent.foreground.r << 16 | button->conponent.foreground.g << 8 | button->conponent.foreground.b
        );
        xOffset++;
        tmp++;
    }

    // 3. register click event
}
