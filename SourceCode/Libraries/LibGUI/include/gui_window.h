//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_component.h>

#ifndef __LIBRARY_LIBGUI_WINDOW_H__
#define __LIBRARY_LIBGUI_WINDOW_H__

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

typedef struct GUIWindow {
    struct GUIComponent component;
    char *title;
    // todo: children
} GUIWindow;

void gui_create_window(GUIWindow *window);

void gui_init_window(GUIWindow *window, uint32_t x, uint32_t y, const char *title);

void gui_draw_window(GUIWindow *window);

#endif //__LIBRARY_LIBGUI_WINDOW_H__
