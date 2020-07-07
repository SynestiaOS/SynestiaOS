//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_component.h>

#ifndef __LIBRARY_LIBGUI_WINDOW_H__
#define __LIBRARY_LIBGUI_WINDOW_H__


typedef struct GUIWindow {
    struct GUIComponent conponent;
    char *title;
    // todo: childrrens
} GUIWindow;

void gui_window(GUIWindow *window, uint32_t x, uint32_t y, const char *title);

void gui_draw_window(GUIWindow *window);

#endif //__LIBRARY_LIBGUI_WINDOW_H__
