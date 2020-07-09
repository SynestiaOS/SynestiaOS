//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_CONTAINER_H__
#define __LIBRARY_LIBGUI_CONTAINER_H__

#include <gui_component.h>

typedef enum Orientation {
    VERTICAL,
    HORIZONTAL,
} Orientation;

typedef struct GUIContainer {
    GUIComponent component;
    Orientation orientation;
    GUIComponent *children;
} GUIWindow;

#endif //__LIBRARY_LIBGUI_CONTAINER_H__
