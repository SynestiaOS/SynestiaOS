//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_LABEL_H__
#define __LIBRARY_LIBGUI_LABEL_H__

#include "libc/stdint.h"
#include "libgui/gui_component.h"
#include "libgfx/gfx2d.h"

typedef struct GUILabel {
    GUIComponent component;
    char text[0xFF];
    uint32_t fontSize;
    GfxSurface surface;
} GUILabel;

void gui_label_create(GUILabel *label);

void gui_label_init(GUILabel *label, uint32_t x, uint32_t y, const char *text);

void gui_label_draw(GUILabel *label);

#endif//__LIBRARY_LIBGUI_LABEL_H__
