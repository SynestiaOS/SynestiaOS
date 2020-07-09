//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_panel.h>
#include <stdbool.h>
#include <gui_button.h>
#include <gui_label.h>
#include <gfx2d.h>
#include <gui_container.h>


void gui_panel_create(GUIPanel *panel) {
    panel->component.type = PANEL;
    panel->component.visable = true;
    panel->component.node.next = nullptr;
    panel->component.node.prev = nullptr;
    panel->children = nullptr;

    panel->component.position.x = 0;
    panel->component.position.y = 0;

    panel->component.size.height = 0;
    panel->component.size.width = 0;

    panel->component.padding.top = 0;
    panel->component.padding.bottom = 0;
    panel->component.padding.left = 0;
    panel->component.padding.right = 0;

    panel->component.margin.top = 0;
    panel->component.margin.bottom = 0;
    panel->component.margin.left = 0;
    panel->component.margin.right = 0;

    panel->component.background.a = 0x00;
    panel->component.background.r = 0xFF;
    panel->component.background.g = 0xFF;
    panel->component.background.b = 0xFF;

    panel->component.foreground.a = 0x00;
    panel->component.foreground.r = 0x00;
    panel->component.foreground.g = 0x00;
    panel->component.foreground.b = 0x00;
}

void gui_panel_init(GUIPanel *panel, uint32_t x, uint32_t y) {
    panel->component.position.x = x;
    panel->component.position.y = y;

    panel->component.padding.top = (panel->component.padding.top == 0 ? DEFAULT_PADDING : panel->component.padding.top);
    panel->component.padding.bottom = (panel->component.padding.bottom == 0 ? DEFAULT_PADDING : panel->component.padding.bottom);
    panel->component.padding.left = (panel->component.padding.left == 0 ? DEFAULT_PADDING : panel->component.padding.left);
    panel->component.padding.right = (panel->component.padding.right == 0 ? DEFAULT_PADDING : panel->component.padding.right);

    panel->component.margin.top = (panel->component.margin.top == 0 ? DEFAULT_MARGIN : panel->component.margin.top);
    panel->component.margin.bottom = (panel->component.margin.bottom == 0 ? DEFAULT_MARGIN : panel->component.margin.bottom);
    panel->component.margin.left = (panel->component.margin.left == 0 ? DEFAULT_MARGIN : panel->component.margin.left);
    panel->component.margin.right = (panel->component.margin.right == 0 ? DEFAULT_MARGIN : panel->component.margin.right);

    if (panel->component.size.width == 0) {
        panel->component.size.width = DEFAULT_PANEL_WIDTH;

    }
    if (panel->component.size.height == 0) {
        panel->component.size.height = DEFAULT_PANEL_HEIGHT;
    }
}

void gui_panel_add_children(GUIPanel *panel, GUIComponent *component) {
    if (panel->children == nullptr) {
        panel->children = component;
    } else {
        klist_append(&(panel->children->node), &(component->node));
    }
}

void gui_panel_draw_children(GUIPanel *panel) {
    GUIComponent *component = panel->children;
    while (component != nullptr) {
        switch (component->type) {
            case BUTTON: {
                GUIButton *button = getNode(component, GUIButton, component);
                button->component.position.x = button->component.position.x + panel->component.position.x + panel->component.padding.left;
                button->component.position.y = button->component.position.y + panel->component.position.y + panel->component.padding.top;
                gui_button_draw(button);
                break;
            }

            case LABEL: {
                GUILabel *label = getNode(component, GUILabel, component);
                label->component.position.x = label->component.position.x + panel->component.position.x + panel->component.padding.left;
                label->component.position.y = label->component.position.y + panel->component.position.y + panel->component.padding.top;
                gui_label_draw(label);
                break;
            }

            case PANEL: {
                GUIPanel *innerPanel = getNode(component, GUIPanel, component);
                innerPanel->component.position.x = innerPanel->component.position.x + panel->component.position.x + panel->component.padding.left;
                innerPanel->component.position.y = innerPanel->component.position.y + panel->component.position.y + panel->component.padding.top;
                gui_panel_draw(innerPanel);
                break;
            }

            case CONTAINER: {
                GUIContainer *innerContainer = getNode(component, GUIContainer, component);
                innerContainer->component.position.x = innerContainer->component.position.x + panel->component.position.x + panel->component.padding.left;
                innerContainer->component.position.y = innerContainer->component.position.y + panel->component.position.y + panel->component.padding.top;
                gui_container_draw(innerContainer);
                break;
            }

            default:
                break;
        }

        component = getNode(component->node.next, GUIComponent, node);
    }
}

void gui_panel_draw(GUIPanel *panel) {
    if (panel->component.visable) {
        // 1. draw_background
        gfx2d_fill_rect(
                panel->component.position.x,
                panel->component.position.y,
                panel->component.position.x + panel->component.size.width,
                panel->component.position.y + panel->component.size.height,
                panel->component.background.r << 16 | panel->component.background.g << 8 | panel->component.background.b
        );

        // 2. draw children
        gui_panel_draw_children(panel);
    }
}
