//
// Created by XingfengYang on 2020/7/7.
//

#include <gfx2d.h>
#include <gui_button.h>
#include <gui_container.h>
#include <gui_label.h>
#include <gui_panel.h>
#include <log.h>
#include <stdbool.h>
#include <stdlib.h>

extern uint32_t GFX2D_BUFFER[1024 * 768];

void gui_panel_create(GUIPanel *panel) {
    panel->component.type = PANEL;
    panel->component.visable = true;
    panel->component.colorMode = RGB;
    panel->component.node.next = nullptr;
    panel->component.node.prev = nullptr;
    panel->children = nullptr;

    panel->component.position.x = 0;
    panel->component.position.y = 0;

    panel->component.size.height = DEFAULT_PANEL_HEIGHT;
    panel->component.size.width = DEFAULT_PANEL_WIDTH;

    panel->component.padding.top = DEFAULT_PADDING;
    panel->component.padding.bottom = DEFAULT_PADDING;
    panel->component.padding.left = DEFAULT_PADDING;
    panel->component.padding.right = DEFAULT_PADDING;

    panel->component.margin.top = DEFAULT_MARGIN;
    panel->component.margin.bottom = DEFAULT_MARGIN;
    panel->component.margin.left = DEFAULT_MARGIN;
    panel->component.margin.right = DEFAULT_MARGIN;

    panel->component.background.a = (FLUENT_PRIMARY_BACK_COLOR >> 24) & 0xFF;
    panel->component.background.r = (FLUENT_PRIMARY_BACK_COLOR >> 16) & 0xFF;
    panel->component.background.g = (FLUENT_PRIMARY_BACK_COLOR >> 8) & 0xFF;
    panel->component.background.b = FLUENT_PRIMARY_BACK_COLOR & 0xFF;

    panel->component.foreground.a = (FLUENT_PRIMARY_FORE_COLOR >> 24) & 0xFF;
    panel->component.foreground.r = (FLUENT_PRIMARY_FORE_COLOR >> 16) & 0xFF;
    panel->component.foreground.g = (FLUENT_PRIMARY_FORE_COLOR >> 8) & 0xFF;
    panel->component.foreground.b = FLUENT_PRIMARY_FORE_COLOR & 0xFF;

    panel->children = kvector_allocate();
    if (panel->children == nullptr) {
        LogError("[GUI]: panel create failed, unable to allocate children vector\n");
    }

    gfx2d_create_context(&panel->context, 1024, 768, GFX2D_BUFFER);
}

void gui_panel_init(GUIPanel *panel, uint32_t x, uint32_t y) {
    panel->component.position.x = x;
    panel->component.position.y = y;
}

void gui_panel_add_children(GUIPanel *panel, GUIComponent *component) {
    if (panel->children != nullptr) {
        kvector_add(panel->children, &(component->node));
    }
}

void gui_panel_draw_children(GUIPanel *panel) {
    KernelVector *children = panel->children;
    if (children != nullptr) {
        for (uint32_t i = 0; i < children->index; i++) {
            ListNode *listNode = children->node[i];
            GUIComponent *component = getNode(listNode, GUIComponent, node);
            switch (component->type) {
                case BUTTON: {
                    GUIButton *button = getNode(component, GUIButton, component);
                    button->component.position.x =
                            button->component.position.x + panel->component.position.x + panel->component.padding.left;
                    button->component.position.y =
                            button->component.position.y + panel->component.position.y + panel->component.padding.top;
                    gui_button_draw(button);
                    break;
                }

                case LABEL: {
                    GUILabel *label = getNode(component, GUILabel, component);
                    label->component.position.x =
                            label->component.position.x + panel->component.position.x + panel->component.padding.left;
                    label->component.position.y =
                            label->component.position.y + panel->component.position.y + panel->component.padding.top;
                    gui_label_draw(label);
                    break;
                }

                case PANEL: {
                    GUIPanel *innerPanel = getNode(component, GUIPanel, component);
                    innerPanel->component.position.x = innerPanel->component.position.x + panel->component.position.x +
                                                       panel->component.padding.left;
                    innerPanel->component.position.y = innerPanel->component.position.y + panel->component.position.y +
                                                       panel->component.padding.top;
                    gui_panel_draw(innerPanel);
                    break;
                }

                case CONTAINER: {
                    GUIContainer *innerContainer = getNode(component, GUIContainer, component);
                    innerContainer->component.position.x =
                            innerContainer->component.position.x + panel->component.position.x +
                            panel->component.padding.left;
                    innerContainer->component.position.y =
                            innerContainer->component.position.y + panel->component.position.y +
                            panel->component.padding.top;
                    gui_container_draw(innerContainer);
                    break;
                }

                default:
                    break;
            }
        }
    }
}

void gui_panel_draw(GUIPanel *panel) {
    if (panel->component.visable) {
        // 1. draw_background
        if (panel->component.colorMode == RGB) {
            panel->context.operations.fillRect(&panel->context, panel->component.position.x,
                                               panel->component.position.y,
                                               panel->component.position.x + panel->component.size.width,
                                               panel->component.position.y + panel->component.size.height,
                                               panel->component.background.r << 16 |
                                                       panel->component.background.g << 8 | panel->component.background.b);
        }

        // 2. draw children
        gui_panel_draw_children(panel);
    }
}
