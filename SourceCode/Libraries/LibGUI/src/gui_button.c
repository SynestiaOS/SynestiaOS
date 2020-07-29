//
// Created by XingfengYang on 2020/7/7.
//
#include <gfx2d.h>
#include <gui_button.h>
#include <stdbool.h>

extern uint32_t GFX2D_BUFFER[1024 * 768];
void gui_button_create(GUIButton *button) {
  button->component.type = BUTTON;
  button->component.visable = true;
  button->component.colorMode = RGB;
  button->component.node.next = nullptr;
  button->component.node.prev = nullptr;

  button->component.position.x = 0;
  button->component.position.y = 0;

  button->component.size.height = 0;
  button->component.size.width = 0;

  button->fontSize = DEFAULT_FONT_SIZE;
  button->component.padding.top = DEFAULT_PADDING;
  button->component.padding.bottom = DEFAULT_PADDING;
  button->component.padding.left = DEFAULT_PADDING;
  button->component.padding.right = DEFAULT_PADDING;

  button->component.margin.top = DEFAULT_MARGIN;
  button->component.margin.bottom = DEFAULT_MARGIN;
  button->component.margin.left = DEFAULT_MARGIN;
  button->component.margin.right = DEFAULT_MARGIN;
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

void gui_button_init(GUIButton *button, uint32_t x, uint32_t y, const char *text) {
  button->component.position.x = x;
  button->component.position.y = y;

  button->text = text;

  char *tmp = text;
  uint32_t length = 0;
  while (*tmp) {
    length++;
    tmp++;
  }

  if (button->component.size.width == 0) {
    button->component.size.width =
        length * button->fontSize + button->component.padding.left + button->component.padding.right;
    if (button->component.size.height == 0) {
      button->component.size.height =
          button->fontSize + button->component.padding.top + button->component.padding.bottom;
    }
  } else {
    if (button->component.size.height == 0) {
      uint32_t lineFonts =
          (button->component.size.width - button->component.padding.left - button->component.padding.right) /
          button->fontSize;
      uint32_t lines = length / lineFonts;
      button->component.size.height =
          lines * button->fontSize + button->component.padding.top + button->component.padding.bottom;
    }
  }
}

void gui_button_draw(GUIButton *button) {
  Gfx2DContext context = {.width = 1024, .height = 768, .buffer = GFX2D_BUFFER};
  if (button->component.visable) {
    // 1. draw_background
    if (button->component.colorMode == RGB) {
      gfx2d_fill_rect(context, button->component.position.x + button->component.margin.left,
                      button->component.position.y + button->component.margin.top,
                      button->component.position.x + button->component.size.width,
                      button->component.position.y + button->component.size.height,
                      button->component.background.r << 16 | button->component.background.g << 8 |
                          button->component.background.b);
    }

    // 2. draw_font
    char *tmp = button->text;
    uint32_t xOffset = 0;
    uint32_t length = 0;
    while (*tmp) {
      length++;
      tmp++;
    }
    uint32_t lineFonts =
        (button->component.size.width - button->component.padding.left - button->component.padding.right) /
        button->fontSize;

    tmp = button->text;
    uint32_t column = 0;
    uint32_t row = 0;
    while (*tmp) {
      gfx2d_draw_ascii(
          context, button->component.position.x + xOffset * button->fontSize + button->component.padding.left,
          button->component.position.y + row * button->fontSize + button->component.padding.top, *tmp,
          button->component.foreground.r << 16 | button->component.foreground.g << 8 | button->component.foreground.b);
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
}
