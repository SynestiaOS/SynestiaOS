//
// Created by XingfengYang on 2020/7/7.
//
#include <gui_button.h>
#include <gfx2d.h>

void gui_button(GUIButton *button, uint32_t x, uint32_t y, const char *text) {
    Position position;
    position.x = x;
    position.y = y;
    button->component.position = position;

    button->text = text;
    button->component.size.height = 24;

    char *tmp = text;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    button->component.size.width = length * 8 + 16;
    Color colorBg;
    colorBg.a = 0x00;
    colorBg.r = 0x00;
    colorBg.g = 0x78;
    colorBg.b = 0xD4;
    button->component.background = colorBg;


    Color colorFore;
    colorFore.a = 0x00;
    colorFore.r = 0xFF;
    colorFore.g = 0xFF;
    colorFore.b = 0xFF;
    button->component.foreground = colorFore;
}

void gui_draw_button(GUIButton *button) {
    // 1. draw_background
    gfx2d_fill_rect(
            button->component.position.x,
            button->component.position.y,
            button->component.position.x + button->component.size.width,
            button->component.position.y + button->component.size.height,
            button->component.background.r << 16 | button->component.background.g << 8 | button->component.background.b
    );

    // 2. draw_font
    char *tmp = button->text;
    uint32_t xOffset = 0;
    while (*tmp) {
        gfx2d_draw_ascii(
                button->component.position.x + xOffset * 8 + 8,
                button->component.position.y + 8,
                *tmp,
                button->component.foreground.r << 16 | button->component.foreground.g << 8 | button->component.foreground.b
        );
        xOffset++;
        tmp++;
    }

    // 3. register click event
}
