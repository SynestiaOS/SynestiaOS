//
// Created by XingfengYang on 2020/7/29.
//

#include <gfx2d.h>
#include <gui_view3d.h>
#include <kheap.h>
#include <log.h>
#include <stdbool.h>
#include <stdlib.h>

void gui_view3d_create(GUIView3D *view) {
  view->component.type = VIEW3D;
  view->component.visable = true;
  view->component.colorMode = RGB;

  view->component.node.next = nullptr;
  view->component.node.prev = nullptr;

  view->component.position.x = 0;
  view->component.position.y = 0;

  view->component.size.height = DEFAULT_CANVAS_HEIGHT;
  view->component.size.width = DEFAULT_CANVAS_WIDTH;

  view->component.padding.top = DEFAULT_PADDING;
  view->component.padding.bottom = DEFAULT_PADDING;
  view->component.padding.left = DEFAULT_PADDING;
  view->component.padding.right = DEFAULT_PADDING;
  view->component.margin.top = DEFAULT_MARGIN;
  view->component.margin.bottom = DEFAULT_MARGIN;
  view->component.margin.left = DEFAULT_MARGIN;
  view->component.margin.right = DEFAULT_MARGIN;

  view->component.background.a = 0x00;
  view->component.background.r = 0xFF;
  view->component.background.g = 0xFF;
  view->component.background.b = 0xFF;
  view->component.foreground.a = 0x00;
  view->component.foreground.r = 0x00;
  view->component.foreground.g = 0x00;
  view->component.foreground.b = 0x00;

  view->buffer = kheap_alloc(view->component.size.width * view->component.size.height * sizeof(uint32_t));
  if (view->buffer == nullptr) {
    LogError("[GUI]: canvas create failed, unable to allocate buffer memory\n");
  }
}