//
// Created by XingfengYang on 2020/7/14.
//

#ifndef __LIBRARY_LIBGUI_VIEW_3D_H__
#define __LIBRARY_LIBGUI_VIEW_3D_H__

#include <gui_component.h>

#define DEFAULT_CANVAS_WIDTH 300
#define DEFAULT_CANVAS_HEIGHT 300

typedef struct GUIView3D {
  GUIComponent component;
  uint32_t *buffer;
} GUIView3D;

void gui_view3d_create(GUIView3D *view);

#endif //__LIBRARY_LIBGUI_VIEW_3D_H__
