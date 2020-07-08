//
// Created by XingfengYang on 2020/7/7.
//
#include <gui_button.h>
#include <gfx2d.h>

void gui_create_button(GUIButton *button) {
    button->component.position.x = 0;
    button->component.position.y = 0;

    button->component.size.height = 0;
    button->component.size.width = 0;

    button->fontSize = 0;
    button->component.padding.top = 0;
    button->component.padding.bottom = 0;
    button->component.padding.left = 0;
    button->component.padding.right = 0;

    button->component.margin.top = 0;
    button->component.margin.bottom = 0;
    button->component.margin.left = 0;
    button->component.margin.right = 0;
    button->text = "";

    button->component.background.a = 0x00;
    button->component.background.r = 0x00;
    button->component.background.g = 0x78;
    button->component.background.b = 0xD4;
    button->component.foreground.a = 0x00;
    button->component.foreground.r = 0xFF;
    button->component.foreground.g = 0xFF;
    button->component.foreground.b = 0xFF;
}

void gui_init_button(GUIButton *button, uint32_t x, uint32_t y, const char *text) {
    button->component.position.x = x;
    button->component.position.y = y;

    button->fontSize = (button->fontSize == 0 ? DEFAULT_FONT_SIZE : button->fontSize);
    button->component.padding.top = (button->component.padding.top == 0 ? DEFAULT_pADDING : button->component.padding.top);
    button->component.padding.bottom = (button->component.padding.bottom == 0 ? DEFAULT_pADDING : button->component.padding.bottom);
    button->component.padding.left = (button->component.padding.left == 0 ? DEFAULT_pADDING : button->component.padding.left);
    button->component.padding.right = (button->component.padding.right == 0 ? DEFAULT_pADDING : button->component.padding.right);

    button->component.margin.top = (button->component.margin.top == 0 ? DEFAULT_MARGIN : button->component.margin.top);
    button->component.margin.bottom = (button->component.margin.bottom == 0 ? DEFAULT_MARGIN : button->component.margin.bottom);
    button->component.margin.left = (button->component.margin.left == 0 ? DEFAULT_MARGIN : button->component.margin.left);
    button->component.margin.right = (button->component.margin.right == 0 ? DEFAULT_MARGIN : button->component.margin.right);

    button->text = text;

    char *tmp = text;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }

    if (button->component.size.width == 0) {
        button->component.size.width = length * button->fontSize + button->component.padding.left + button->component.padding.right;
        if (button->component.size.height == 0) {
            button->component.size.height = button->fontSize + button->component.padding.top + button->component.padding.bottom;
        }
    } else {
        if (button->component.size.height == 0) {
            uint32_t lineFonts = (button->component.size.width - button->component.padding.left - button->component.padding.right) / button->fontSize;
            uint32_t lines = length / lineFonts;
            button->component.size.height = lines * button->fontSize + button->component.padding.top + button->component.padding.bottom;
        }
    }
    if (button->component.background.a == 0x00 &&
        button->component.background.r == 0x00 &&
        button->component.background.g == 0x78 &&
        button->component.background.b == 0xD4) {
        button->component.background.a = 0x00;
        button->component.background.r = 0x00;
        button->component.background.g = 0x78;
        button->component.background.b = 0xD4;
    }

    if (button->component.foreground.a == 0x00 &&
        button->component.foreground.r == 0xFF &&
        button->component.foreground.g == 0xFF &&
        button->component.foreground.b == 0xFF) {
        button->component.foreground.a = 0x00;
        button->component.foreground.r = 0xFF;
        button->component.foreground.g = 0xFF;
        button->component.foreground.b = 0xFF;
    }
}

void gui_draw_button(GUIButton *button) {
    // 1. draw_background
    gfx2d_fill_rect(
            button->component.position.x + button->component.margin.left,
            button->component.position.y + button->component.margin.top,
            button->component.position.x + button->component.size.width,
            button->component.position.y + button->component.size.height,
            button->component.background.r << 16 | button->component.background.g << 8 | button->component.background.b
    );

    // 2. draw_font
    char *tmp = button->text;
    uint32_t xOffset = 0;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }
    uint32_t lineFonts = (button->component.size.width - button->component.padding.left - button->component.padding.right) / button->fontSize;

    tmp = button->text;
    uint32_t column = 0;
    uint32_t row = 0;
    while (*tmp) {
        gfx2d_draw_ascii(
                button->component.position.x + xOffset * button->fontSize + button->component.padding.left,
                button->component.position.y + row * button->fontSize + button->component.padding.top,
                *tmp,
                button->component.foreground.r << 16 | button->component.foreground.g << 8 | button->component.foreground.b
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
