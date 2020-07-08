//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_LABEL_H__
#define __LIBRARY_LIBGUI_LABEL_H__

#include <stdint.h>
#include <gui_component.h>

typedef struct GUILabel {
    struct GUIComponent component;
    char *text;
    uint32_t fontSize;
} GUILabel;

void gui_label_create(GUILabel *label);

void gui_label_init(GUILabel *label, uint32_t x, uint32_t y, const char *text);

void gui_label_draw(GUILabel *label);


#endif //__LIBRARY_LIBGUI_LABEL_H__
