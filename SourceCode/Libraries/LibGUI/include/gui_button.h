//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_BUTTON_H__
#define __LIBRARY_LIBGUI_BUTTON_H__

#include <gui_component.h>

typedef struct GUIButton {
    struct GUIComponent component;
    char *text;
    uint32_t fontSize;
} GUIButton;


void gui_create_button(GUIButton *button);

void gui_init_button(GUIButton *button, uint32_t x, uint32_t y, const char *text);

void gui_draw_button(GUIButton *button);

#endif //__LIBRARY_LIBGUI_BUTTON_H__
