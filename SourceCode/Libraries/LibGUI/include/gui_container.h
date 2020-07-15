//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_CONTAINER_H__
#define __LIBRARY_LIBGUI_CONTAINER_H__

#include <gui_component.h>
#include <kvector.h>

#define DEFAULT_CONTAINER_WIDTH 300
#define DEFAULT_CONTAINER_HEIGHT 300

typedef enum Orientation {
  VERTICAL,
  HORIZONTAL,
} Orientation;

typedef struct GUIContainer {
  GUIComponent component;
  Orientation orientation;
  KernelVector *children;
} GUIContainer;

void gui_container_create(GUIContainer *container);

void gui_container_init(GUIContainer *container, uint32_t x, uint32_t y, Orientation orientation);

void gui_container_add_children(GUIContainer *container, GUIComponent *component);

void gui_container_draw_children(GUIContainer *container, Orientation orientation);

void gui_container_draw(GUIContainer *container);

#endif //__LIBRARY_LIBGUI_CONTAINER_H__
