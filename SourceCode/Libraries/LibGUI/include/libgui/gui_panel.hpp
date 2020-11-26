//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_PANEL_H__
#define __LIBRARY_LIBGUI_PANEL_H__

#include "kernel/kvector.hpp"
#include "libgui/gui_component.hpp"

#define DEFAULT_PANEL_WIDTH 200
#define DEFAULT_PANEL_HEIGHT 200

typedef struct GUIPanel {
    GUIComponent component;
    KernelVector *children;
    Gfx2DContext context;
} GUIPanel;

void gui_panel_create(GUIPanel *panel);

void gui_panel_init(GUIPanel *panel, uint32_t x, uint32_t y);

void gui_panel_add_children(GUIPanel *panel, GUIComponent *component);

void gui_panel_draw_children(GUIPanel *panel);

void gui_panel_draw(GUIPanel *panel);

#endif//__LIBRARY_LIBGUI_PANEL_H__
