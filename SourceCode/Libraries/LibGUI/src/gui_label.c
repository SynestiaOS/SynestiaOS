//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_label.h>
#include <gfx2d.h>

void gui_label(GUILabel *label, uint32_t x, uint32_t y, const char *text) {
    Position position;
    position.x = x;
    position.y = y;
    label->component.position = position;
    label->text = text;

    char *tmp = text;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    if (label->component.size.width == 0) {
        label->component.size.width = length * 8 + 16;
        label->component.size.height = 24;
    } else {
        uint32_t lineFonts = (label->component.size.width - 16) / 8;
        uint32_t lines = length / lineFonts;
        label->component.size.height = lines * 24;
    }

    Color colorBg;
    colorBg.a = 0x00;
    colorBg.r = 0xFF;
    colorBg.g = 0xFF;
    colorBg.b = 0xFF;
    label->component.background = colorBg;


    Color colorFore;
    colorFore.a = 0x00;
    colorFore.r = 0x00;
    colorFore.g = 0x00;
    colorFore.b = 0x00;
    label->component.foreground = colorFore;
}

void gui_draw_label(GUILabel *label) {
    gfx2d_fill_rect(
            label->component.position.x,
            label->component.position.y,
            label->component.position.x + label->component.size.width,
            label->component.position.y + label->component.size.height,
            label->component.background.r << 16 | label->component.background.g << 8 | label->component.background.b
    );

    // 2. draw_font
    char *tmp = label->text;
    uint32_t xOffset = 0;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    uint32_t lineFonts = (label->component.size.width - 16) / 8;

    tmp = label->text;
    uint32_t column = 0;
    uint32_t row = 0;
    while (*tmp) {
        gfx2d_draw_ascii(
                label->component.position.x + xOffset * 8 + 8,
                label->component.position.y + row * 8 + 8,
                *tmp,
                label->component.foreground.r << 16 | label->component.foreground.g << 8 | label->component.foreground.b
        );
        column++;
        if (column == lineFonts) {
            row++;
            xOffset = 0;
            column = 0;
        }

        xOffset++;
        tmp++;
    }

    // 3. register click event
}
