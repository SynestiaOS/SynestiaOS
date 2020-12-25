//
// Created by XingfengYang on 2020/7/29.
//

#include "libgui/gui_view3d.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "libgfx/gfx2d.h"

extern Heap kernelHeap;
extern uint32_t GFX2D_BUFFER[1024 * 768];

void gui_view3d_create(GUIView3D *view) {
    view->component.type = VIEW3D;
    view->component.visable = true;
    view->component.colorMode = RGB;

    view->component.node.next = nullptr;
    view->component.node.prev = nullptr;

    view->component.position.x = 0;
    view->component.position.y = 0;

    view->component.size.height = DEFAULT_VIEW3D_HEIGHT;
    view->component.size.width = DEFAULT_VIEW3D_WIDTH;

    view->component.padding.top = DEFAULT_PADDING;
    view->component.padding.bottom = DEFAULT_PADDING;
    view->component.padding.left = DEFAULT_PADDING;
    view->component.padding.right = DEFAULT_PADDING;
    view->component.margin.top = DEFAULT_MARGIN;
    view->component.margin.bottom = DEFAULT_MARGIN;
    view->component.margin.left = DEFAULT_MARGIN;
    view->component.margin.right = DEFAULT_MARGIN;

    view->component.background.a = 0x00;
    view->component.background.r = 0xFF;
    view->component.background.g = 0xFF;
    view->component.background.b = 0xFF;
    view->component.foreground.a = 0x00;
    view->component.foreground.r = 0x00;
    view->component.foreground.g = 0x00;
    view->component.foreground.b = 0x00;

    view->buffer = kernelHeap.operations.alloc(&kernelHeap, view->component.size.width * view->component.size.height *
                                                            sizeof(uint32_t));
    if (view->buffer == nullptr) {
        LogError("[GUI]: canvas create failed, unable to allocate buffer memory\n");
    }

    gfx2d_create_context(&view->context, 1024, 768, GFX2D_BUFFER);
}

void gui_view3d_init(GUIView3D *view, uint32_t x, uint32_t y) {
    view->component.position.x = x;
    view->component.position.y = y;
    // Mesh m = {
    //   .tris=nullptr
    // };
    // view->mesh = m;
    // view->matProjection = gfx3d_matrix_make_projection(90.0f, view->component.size.height / view->component.size.width,
    // 0.1f, 1000.0f);
}

void gui_view3d_draw(GUIView3D *view) {
    view->context.operations.drawBitmap(&view->context, view->component.position.x, view->component.position.y,
                                        view->component.size.width,
                                        view->component.size.height, view->buffer);
}
