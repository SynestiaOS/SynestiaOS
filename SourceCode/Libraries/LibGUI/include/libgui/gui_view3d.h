//
// Created by XingfengYang on 2020/7/14.
//

#ifndef __LIBRARY_LIBGUI_VIEW_3D_H__
#define __LIBRARY_LIBGUI_VIEW_3D_H__

#include "libgfx/gfx3d.h"
#include "libgui/gui_component.h"
#include "libgfx/gfx2d.h"

#define DEFAULT_VIEW3D_WIDTH 200
#define DEFAULT_VIEW3D_HEIGHT 150

typedef struct GUIView3D {
    GUIComponent component;
    Mesh mesh;
    Mat4x4 matProjection;
    Vec3D vCamera;
    Vec3D vLookDir;
    float fYaw;
    uint32_t *buffer;
    Gfx2DContext context;
} GUIView3D;

void gui_view3d_create(GUIView3D *view);

void gui_view3d_init(GUIView3D *view, uint32_t x, uint32_t y);

void gui_view3d_draw(GUIView3D *view);

#endif//__LIBRARY_LIBGUI_VIEW_3D_H__
