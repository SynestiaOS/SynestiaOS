//
// Created by XingfengYang on 2020/7/14.
//

#ifndef __LIBRARY_LIBGUI_CANVAS_3D_H__
#define __LIBRARY_LIBGUI_CANVAS_3D_H__

#include <gui_component.h>

#define DEFAULT_CANVAS_WIDTH 300
#define DEFAULT_CANVAS_HEIGHT 300

typedef struct GUICanvas3D {
  GUIComponent component;
  uint32_t *buffer;
} GUICanvas3D;

void gui_canvas_3d_create(GUICanvas3D *canvas);

#endif //__LIBRARY_LIBGUI_CANVAS_3D_H__
