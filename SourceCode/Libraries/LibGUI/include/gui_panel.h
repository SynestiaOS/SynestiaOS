//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_PANEL_H__
#define __LIBRARY_LIBGUI_PANEL_H__

#include <gui_component.h>

typedef struct GUIPanel {
    GUIComponent component;
    GUIComponent *children;
} GUIPanel;

#endif //__LIBRARY_LIBGUI_PANEL_H__
