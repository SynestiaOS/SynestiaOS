//
// Created by XingfengYang on 2020/7/29.
//

#include <gfx2d.h>
#include <gui_canvas_3d.h>
#include <kheap.h>
#include <log.h>
#include <stdbool.h>
#include <stdlib.h>

void gui_canvas_3d_create(GUICanvas3D *canvas) {
  canvas->component.type = CANVAS;
  canvas->component.visable = true;
  canvas->component.colorMode = RGB;

  canvas->component.node.next = nullptr;
  canvas->component.node.prev = nullptr;

  canvas->component.position.x = 0;
  canvas->component.position.y = 0;

  canvas->component.size.height = DEFAULT_CANVAS_HEIGHT;
  canvas->component.size.width = DEFAULT_CANVAS_WIDTH;

  canvas->component.padding.top = DEFAULT_PADDING;
  canvas->component.padding.bottom = DEFAULT_PADDING;
  canvas->component.padding.left = DEFAULT_PADDING;
  canvas->component.padding.right = DEFAULT_PADDING;
  canvas->component.margin.top = DEFAULT_MARGIN;
  canvas->component.margin.bottom = DEFAULT_MARGIN;
  canvas->component.margin.left = DEFAULT_MARGIN;
  canvas->component.margin.right = DEFAULT_MARGIN;

  canvas->component.background.a = 0x00;
  canvas->component.background.r = 0xFF;
  canvas->component.background.g = 0xFF;
  canvas->component.background.b = 0xFF;
  canvas->component.foreground.a = 0x00;
  canvas->component.foreground.r = 0x00;
  canvas->component.foreground.g = 0x00;
  canvas->component.foreground.b = 0x00;

  canvas->buffer = kheap_alloc(canvas->component.size.width * canvas->component.size.height * sizeof(uint32_t));
  if (canvas->buffer == nullptr) {
    LogError("[GUI]: canvas create failed, unable to allocate buffer memory\n");
  }
}