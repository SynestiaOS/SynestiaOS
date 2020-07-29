//
// Created by XingfengYang on 2020/7/7.
//

#include <gfx2d.h>
#include <gui_label.h>
#include <stdbool.h>

void gui_label_create(GUILabel *label) {
  label->component.type = LABEL;
  label->component.visable = true;
  label->component.colorMode = RGB;
  label->component.node.next = nullptr;
  label->component.node.prev = nullptr;

  label->component.position.x = 0;
  label->component.position.y = 0;

  label->component.size.height = 0;
  label->component.size.width = 0;

  label->fontSize = DEFAULT_FONT_SIZE;
  label->component.padding.top = 0;
  label->component.padding.bottom = 0;
  label->component.padding.left = 0;
  label->component.padding.right = 0;

  label->component.margin.top = 0;
  label->component.margin.bottom = 0;
  label->component.margin.left = 0;
  label->component.margin.right = 0;
  label->text = "";

  label->component.background.a = (FLUENT_PRIMARY_BACK_COLOR >> 24) & 0xFF;
  label->component.background.r = (FLUENT_PRIMARY_BACK_COLOR >> 16) & 0xFF;
  label->component.background.g = (FLUENT_PRIMARY_BACK_COLOR >> 8) & 0xFF;
  label->component.background.b = FLUENT_PRIMARY_BACK_COLOR & 0xFF;

  label->component.foreground.a = (FLUENT_PRIMARY_FORE_COLOR >> 24) & 0xFF;
  label->component.foreground.r = (FLUENT_PRIMARY_FORE_COLOR >> 16) & 0xFF;
  label->component.foreground.g = (FLUENT_PRIMARY_FORE_COLOR >> 8) & 0xFF;
  label->component.foreground.b = FLUENT_PRIMARY_FORE_COLOR & 0xFF;
}

void gui_label_init(GUILabel *label, uint32_t x, uint32_t y, const char *text) {
  label->component.position.x = x;
  label->component.position.y = y;

  label->text = text;

  char *tmp = text;
  uint32_t length = 0;
  while (*tmp) {
    length++;
    tmp++;
  }

  if (label->component.size.width == 0) {
    label->component.size.width =
        length * label->fontSize + label->component.padding.left + label->component.padding.right;
    if (label->component.size.height == 0) {
      label->component.size.height = label->fontSize + label->component.padding.top + label->component.padding.bottom;
    }
  } else {
    if (label->component.size.height == 0) {
      uint32_t lineFonts =
          (label->component.size.width - label->component.padding.left - label->component.padding.right) /
          label->fontSize;
      uint32_t lines = length / lineFonts;
      label->component.size.height =
          lines * label->fontSize + label->component.padding.top + label->component.padding.bottom;
    }
  }
}

void gui_label_draw(GUILabel *label) {
  if (label->component.visable) {
    // 1. draw_background
    if (label->component.colorMode == RGB) {
      gfx2d_fill_rect(SCREEN_BUFFER, label->component.position.x + label->component.margin.left,
                      label->component.position.y + label->component.margin.top,
                      label->component.position.x + label->component.size.width,
                      label->component.position.y + label->component.size.height,
                      label->component.background.r << 16 | label->component.background.g << 8 |
                          label->component.background.b);
    }

    // 2. draw_font
    char *tmp = label->text;
    uint32_t xOffset = 0;
    uint32_t length = 0;
    while (*tmp) {
      length++;
      tmp++;
    }
    uint32_t lineFonts =
        (label->component.size.width - label->component.padding.left - label->component.padding.right) /
        label->fontSize;

    tmp = label->text;
    uint32_t column = 0;
    uint32_t row = 0;
    while (*tmp) {
      gfx2d_draw_ascii(
          SCREEN_BUFFER, label->component.position.x + xOffset * label->fontSize + label->component.padding.left,
          label->component.position.y + row * label->fontSize + label->component.padding.top, *tmp,
          label->component.foreground.r << 16 | label->component.foreground.g << 8 | label->component.foreground.b);
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
}
