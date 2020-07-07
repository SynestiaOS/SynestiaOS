//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_BUTTON_H__
#define __LIBRARY_LIBGUI_BUTTON_H__

#include <gui_component.h>

typedef struct GUIButton {
    struct GUIComponent conponent;
    char *text;
} GUIButton;

void gui_button(GUIButton *button, uint32_t x, uint32_t y, const char *text);

void gui_draw_button(GUIButton *button);

#endif //__LIBRARY_LIBGUI_BUTTON_H__
