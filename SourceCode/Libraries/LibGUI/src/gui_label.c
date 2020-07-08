//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_label.h>
#include <gfx2d.h>


void gui_label_create(GUILabel *label) {
    label->component.type = LABEL;
    label->component.node.next = nullptr;
    label->component.node.prev = nullptr;

    label->component.position.x = 0;
    label->component.position.y = 0;

    label->component.size.height = 0;
    label->component.size.width = 0;

    label->fontSize = 0;
    label->component.padding.top = 0;
    label->component.padding.bottom = 0;
    label->component.padding.left = 0;
    label->component.padding.right = 0;

    label->component.margin.top = 0;
    label->component.margin.bottom = 0;
    label->component.margin.left = 0;
    label->component.margin.right = 0;
    label->text = "";

    label->component.background.a = 0x00;
    label->component.background.r = 0xFF;
    label->component.background.g = 0xFF;
    label->component.background.b = 0xFF;

    label->component.foreground.a = 0x00;
    label->component.foreground.r = 0x00;
    label->component.foreground.g = 0x00;
    label->component.foreground.b = 0x00;
}

void gui_label_init(GUILabel *label, uint32_t x, uint32_t y, const char *text) {
    label->component.position.x = x;
    label->component.position.y = y;

    label->fontSize = (label->fontSize == 0 ? DEFAULT_FONT_SIZE : label->fontSize);
    label->component.padding.top = (label->component.padding.top == 0 ? DEFAULT_PADDING : label->component.padding.top);
    label->component.padding.bottom = (label->component.padding.bottom == 0 ? DEFAULT_PADDING : label->component.padding.bottom);
    label->component.padding.left = (label->component.padding.left == 0 ? DEFAULT_PADDING : label->component.padding.left);
    label->component.padding.right = (label->component.padding.right == 0 ? DEFAULT_PADDING : label->component.padding.right);

    label->component.margin.top = (label->component.margin.top == 0 ? DEFAULT_MARGIN : label->component.margin.top);
    label->component.margin.bottom = (label->component.margin.bottom == 0 ? DEFAULT_MARGIN : label->component.margin.bottom);
    label->component.margin.left = (label->component.margin.left == 0 ? DEFAULT_MARGIN : label->component.margin.left);
    label->component.margin.right = (label->component.margin.right == 0 ? DEFAULT_MARGIN : label->component.margin.right);

    label->text = text;

    char *tmp = text;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }

    if (label->component.size.width == 0) {
        label->component.size.width = length * label->fontSize + label->component.padding.left + label->component.padding.right;
        if (label->component.size.height == 0) {
            label->component.size.height = label->fontSize + label->component.padding.top + label->component.padding.bottom;
        }
    } else {
        if (label->component.size.height == 0) {
            uint32_t lineFonts = (label->component.size.width - label->component.padding.left - label->component.padding.right) / label->fontSize;
            uint32_t lines = length / lineFonts;
            label->component.size.height = lines * label->fontSize + label->component.padding.top + label->component.padding.bottom;
        }
    }
}

void gui_label_draw(GUILabel *label) {
    // 1. draw_background
    gfx2d_fill_rect(
            label->component.position.x + label->component.margin.left,
            label->component.position.y + label->component.margin.top,
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
    uint32_t lineFonts = (label->component.size.width - label->component.padding.left - label->component.padding.right) / label->fontSize;

    tmp = label->text;
    uint32_t column = 0;
    uint32_t row = 0;
    while (*tmp) {
        gfx2d_draw_ascii(
                label->component.position.x + xOffset * label->fontSize + label->component.padding.left,
                label->component.position.y + row * label->fontSize + label->component.padding.top,
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
}
