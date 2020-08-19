//
// Created by XingfengYang on 2020/7/7.
//

#include <gfx2d.h>
#include <gui_button.h>
#include <gui_canvas.h>
#include <gui_container.h>
#include <gui_label.h>
#include <gui_panel.h>
#include <gui_view3d.h>
#include <gui_window.h>
#include <log.h>
#include <stdbool.h>
#include <stdlib.h>

extern uint32_t GFX2D_BUFFER[1024 * 768];
void gui_window_create(GUIWindow *window) {
  window->component.type = WINDOW;
  window->component.visable = true;
  window->component.colorMode = RGB;
  window->component.node.next = nullptr;
  window->component.node.prev = nullptr;
  window->children = nullptr;

  window->component.position.x = 0;
  window->component.position.y = 0;

  window->component.size.height = DEFAULT_WINDOW_HEIGHT;
  window->component.size.width = DEFAULT_WINDOW_WIDTH;

  window->component.padding.top = DEFAULT_PADDING;
  window->component.padding.bottom = DEFAULT_PADDING;
  window->component.padding.left = DEFAULT_PADDING;
  window->component.padding.right = DEFAULT_PADDING;

  window->component.margin.top = DEFAULT_MARGIN;
  window->component.margin.bottom = DEFAULT_MARGIN;
  window->component.margin.left = DEFAULT_MARGIN;
  window->component.margin.right = DEFAULT_MARGIN;

  window->component.background.a = (FLUENT_PRIMARY_BACK_COLOR >> 24) & 0xFF;
  window->component.background.r = (FLUENT_PRIMARY_BACK_COLOR >> 16) & 0xFF;
  window->component.background.g = (FLUENT_PRIMARY_BACK_COLOR >> 8) & 0xFF;
  window->component.background.b = FLUENT_PRIMARY_BACK_COLOR & 0xFF;

  window->component.foreground.a = (FLUENT_PRIMARY_FORE_COLOR >> 24) & 0xFF;
  window->component.foreground.r = (FLUENT_PRIMARY_FORE_COLOR >> 16) & 0xFF;
  window->component.foreground.g = (FLUENT_PRIMARY_FORE_COLOR >> 8) & 0xFF;
  window->component.foreground.b = FLUENT_PRIMARY_FORE_COLOR & 0xFF;

  window->title = "";

  window->children = kvector_allocate();
  if (window->children == nullptr) {
    LogError("[GUI]: window create failed, unable to allocate children vector\n");
  }
}

void gui_window_init(GUIWindow *window, uint32_t x, uint32_t y, const char *title) {
  window->component.position.x = x;
  window->component.position.y = y;

  window->title = title;

  char *tmp = title;
  uint32_t length = 0;
  while (*tmp) {
    length++;
    tmp++;
  }
}

void gui_window_add_children(GUIWindow *window, GUIComponent *component) {
  if (window->children != nullptr) {
    kvector_add(window->children, &(component->node));
  }
}

void gui_window_draw(GUIWindow *window) {
  Gfx2DContext context = {.width = 1024, .height = 768, .buffer = GFX2D_BUFFER};
  if (window->component.visable) {
    if (window->component.colorMode == RGB) {
      // 1. draw_background
      gfx2d_fill_rect(context, window->component.position.x, window->component.position.y,
                      window->component.position.x + window->component.size.width,
                      window->component.position.y + window->component.size.height + DEFAULT_WINDOW_HEADER_HEIGHT,
                      window->component.background.r << 16 | window->component.background.g << 8 |
                          window->component.background.b);
    }

    // 2. draw header
    gfx2d_fill_rect(context, window->component.position.x, window->component.position.y,
                    window->component.position.x + window->component.size.width,
                    window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT, FLUENT_PRIMARY_COLOR);

    uint16_t *bitmap = win_app_16_bits();
    for (uint32_t i = 0; i < 16; i++) {
      for (uint32_t j = 0; j < 16; j++) {
        if ((bitmap[i] & (0x1 << j)) > 0) {
          gfx2d_write_pixel_color(context, window->component.position.x + j + DEFAULT_PADDING,
                                  window->component.position.y + i + DEFAULT_PADDING + 4, 0xFFFFFF);
        }
      }
    }

    // 3. draw_font
    char *tmp = window->title;
    uint32_t xOffset = 2;
    while (*tmp) {
      gfx2d_draw_ascii(context, window->component.position.x + xOffset * DEFAULT_FONT_SIZE + 2 * DEFAULT_PADDING,
                       window->component.position.y + 2 * DEFAULT_PADDING, *tmp, 0xFFFFFF);
      xOffset++;
      tmp++;
    }

    // 4. draw header window
    uint16_t *minBitmap = win_min_16_bits();
    for (uint32_t i = 0; i < 16; i++) {
      for (uint32_t j = 0; j < 16; j++) {
        if ((minBitmap[i] & (0x1 << j)) > 0) {
          gfx2d_write_pixel_color(context, window->component.position.x + j + window->component.size.width - 24 * 3,
                                  window->component.position.y + i + DEFAULT_PADDING + 4, 0xFFFFFF);
        }
      }
    }

    uint16_t *maxBitmap = win_max_16_bits();
    for (uint32_t i = 0; i < 16; i++) {
      for (uint32_t j = 0; j < 16; j++) {
        if ((maxBitmap[i] & (0x1 << j)) > 0) {
          gfx2d_write_pixel_color(context, window->component.position.x + j + window->component.size.width - 24 * 2,
                                  window->component.position.y + i + DEFAULT_PADDING + 4, 0xFFFFFF);
        }
      }
    }

    uint16_t *closeBitmap = win_close_16_bits();
    for (uint32_t i = 0; i < 16; i++) {
      for (uint32_t j = 0; j < 16; j++) {
        if ((closeBitmap[i] & (0x1 << j)) > 0) {
          gfx2d_write_pixel_color(context, window->component.position.x + j + window->component.size.width - 24,
                                  window->component.position.y + i + DEFAULT_PADDING + 4, 0xFFFFFF);
        }
      }
    }

    // 6. draw children
    gui_window_draw_children(window);

    // 7. register click event

    // 7. register drag event
  }
}

void gui_window_draw_children(GUIWindow *window) {
  KernelVector *children = window->children;
  if (children != nullptr) {
    for (uint32_t i = 0; i < children->index; i++) {
      ListNode *listNode = children->node[i];
      GUIComponent *component = getNode(listNode, GUIComponent, node);
      switch (component->type) {
      case BUTTON: {
        GUIButton *button = getNode(component, GUIButton, component);
        button->component.position.x =
            button->component.position.x + window->component.position.x + window->component.padding.left;
        button->component.position.y = button->component.position.y + window->component.position.y +
                                       DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
        gui_button_draw(button);
        break;
      }

      case LABEL: {
        GUILabel *label = getNode(component, GUILabel, component);
        label->component.position.x =
            label->component.position.x + window->component.position.x + window->component.padding.left;
        label->component.position.y = label->component.position.y + window->component.position.y +
                                      DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
        gui_label_draw(label);
        break;
      }

      case CANVAS: {
        GUICanvas *canvas = getNode(component, GUICanvas, component);
        canvas->component.position.x = window->component.position.x + window->component.padding.left;
        canvas->component.position.y =
            window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
        gui_canvas_draw(canvas);
        break;
      }

      case VIEW3D: {
        GUIView3D *view = getNode(component, GUIView3D, component);
        view->component.position.x = window->component.position.x + window->component.padding.left;
        view->component.position.y =
            window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
        gui_view3d_draw(view);
        break;
      }

      case PANEL: {
        GUIPanel *innerPanel = getNode(component, GUIPanel, component);
        innerPanel->component.position.x =
            innerPanel->component.position.x + window->component.position.x + window->component.padding.left;
        innerPanel->component.position.y = innerPanel->component.position.y + window->component.position.y +
                                           DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
        gui_panel_draw(innerPanel);
        break;
      }

      case CONTAINER: {
        GUIContainer *innerContainer = getNode(component, GUIContainer, component);
        innerContainer->component.position.x =
            innerContainer->component.position.x + window->component.position.x + window->component.padding.left;
        innerContainer->component.position.y = innerContainer->component.position.y + window->component.position.y +
                                               DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
        gui_container_draw(innerContainer);
        break;
      }
      default:
        break;
      }
    }
  }
}
