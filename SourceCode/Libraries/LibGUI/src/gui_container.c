//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_container.h>
#include <stdbool.h>
#include <gfx2d.h>
#include <gui_button.h>
#include <gui_label.h>
#include <gui_panel.h>
#include <kvector.h>
#include <stdlib.h>

void gui_container_create(GUIContainer *container) {
    container->component.type = CONTAINER;
    container->component.visable = true;
    container->component.colorMode = RGB;
    container->orientation = VERTICAL;
    container->component.node.next = nullptr;
    container->component.node.prev = nullptr;
    container->children = nullptr;

    container->component.position.x = 0;
    container->component.position.y = 0;

    container->component.size.height = 0;
    container->component.size.width = 0;

    container->component.padding.top = 0;
    container->component.padding.bottom = 0;
    container->component.padding.left = 0;
    container->component.padding.right = 0;

    container->component.margin.top = 0;
    container->component.margin.bottom = 0;
    container->component.margin.left = 0;
    container->component.margin.right = 0;

    container->component.background.a = 0x00;
    container->component.background.r = 0xFF;
    container->component.background.g = 0xFF;
    container->component.background.b = 0xFF;

    container->component.foreground.a = 0x00;
    container->component.foreground.r = 0x00;
    container->component.foreground.g = 0x00;
    container->component.foreground.b = 0x00;

    container->children = kvector_allocate();
    if (container->children == nullptr) {
        printf("[GUI]: container create failed, unable to allocate children vector\n");
    }
}

void gui_container_init(GUIContainer *container, uint32_t x, uint32_t y, Orientation orientation) {
    container->component.position.x = x;
    container->component.position.y = y;
    container->orientation = orientation;

    container->component.padding.top = (container->component.padding.top == 0 ? DEFAULT_PADDING : container->component.padding.top);
    container->component.padding.bottom = (container->component.padding.bottom == 0 ? DEFAULT_PADDING : container->component.padding.bottom);
    container->component.padding.left = (container->component.padding.left == 0 ? DEFAULT_PADDING : container->component.padding.left);
    container->component.padding.right = (container->component.padding.right == 0 ? DEFAULT_PADDING : container->component.padding.right);

    container->component.margin.top = (container->component.margin.top == 0 ? DEFAULT_MARGIN : container->component.margin.top);
    container->component.margin.bottom = (container->component.margin.bottom == 0 ? DEFAULT_MARGIN : container->component.margin.bottom);
    container->component.margin.left = (container->component.margin.left == 0 ? DEFAULT_MARGIN : container->component.margin.left);
    container->component.margin.right = (container->component.margin.right == 0 ? DEFAULT_MARGIN : container->component.margin.right);

    if (container->component.size.width == 0) {
        container->component.size.width = DEFAULT_CONTAINER_WIDTH;

    }
    if (container->component.size.height == 0) {
        container->component.size.height = DEFAULT_CONTAINER_HEIGHT;
    }
}

void gui_container_add_children(GUIContainer *container, GUIComponent *component) {
    if (container->children != nullptr) {
        kvector_add(container->children, &(component->node));
    }
}

void gui_container_draw_children(GUIContainer *container, Orientation orientation) {
    KernelVector *children = container->children;
    if (children != nullptr) {
        if (container->orientation == VERTICAL) {
            uint32_t yOffset = 0;
            for (uint32_t i = 0; i < children->index; i++) {
                ListNode *listNode = children->node[i];
                GUIComponent *component = getNode(listNode, GUIComponent, node);
                switch (component->type) {
                    case BUTTON: {
                        GUIButton *button = getNode(component, GUIButton, component);
                        button->component.position.x = button->component.position.x + container->component.position.x + container->component.padding.left;
                        button->component.position.y = button->component.position.y + container->component.position.y + container->component.padding.top + yOffset;
                        yOffset += button->component.size.height + button->component.margin.top + button->component.margin.bottom;
                        gui_button_draw(button);
                        break;
                    }

                    case LABEL: {
                        GUILabel *label = getNode(component, GUILabel, component);
                        label->component.position.x = label->component.position.x + container->component.position.x + container->component.padding.left;
                        label->component.position.y = label->component.position.y + container->component.position.y + container->component.padding.top + yOffset;
                        yOffset += label->component.size.height + label->component.margin.top + label->component.margin.bottom;
                        gui_label_draw(label);
                        break;
                    }

                    case PANEL: {
                        GUIPanel *innerPanel = getNode(component, GUIPanel, component);
                        innerPanel->component.position.x = innerPanel->component.position.x + container->component.position.x + container->component.padding.left;
                        innerPanel->component.position.y = innerPanel->component.position.y + container->component.position.y + container->component.padding.top + yOffset;
                        yOffset += innerPanel->component.size.height + innerPanel->component.margin.top + innerPanel->component.margin.bottom;
                        gui_panel_draw(innerPanel);
                        break;
                    }

                    case CONTAINER: {
                        GUIContainer *innerContainer = getNode(component, GUIContainer, component);
                        innerContainer->component.position.x = innerContainer->component.position.x + container->component.position.x + container->component.padding.left;
                        innerContainer->component.position.y = innerContainer->component.position.y + container->component.position.y + container->component.padding.top + yOffset;
                        yOffset += innerContainer->component.size.height + innerContainer->component.margin.top + innerContainer->component.margin.bottom;
                        gui_container_draw(innerContainer);
                        break;
                    }

                    default:
                        break;
                }
            }
        } else {
            uint32_t xOffset = 0;
            for (uint32_t i = 0; i < children->index; i++) {
                ListNode *listNode = children->node[i];
                GUIComponent *component = getNode(listNode, GUIComponent, node);
                switch (component->type) {
                    case BUTTON: {
                        GUIButton *button = getNode(component, GUIButton, component);
                        button->component.position.x = button->component.position.x + container->component.position.x + container->component.padding.left + xOffset;
                        button->component.position.y = button->component.position.y + container->component.position.y + container->component.padding.top;
                        xOffset += button->component.size.width + button->component.margin.left + button->component.margin.right;
                        gui_button_draw(button);
                        break;
                    }

                    case LABEL: {
                        GUILabel *label = getNode(component, GUILabel, component);
                        label->component.position.x = label->component.position.x + container->component.position.x + container->component.padding.left + xOffset;
                        label->component.position.y = label->component.position.y + container->component.position.y + container->component.padding.top;
                        xOffset += label->component.size.width + label->component.margin.left + label->component.margin.right;
                        gui_label_draw(label);
                        break;
                    }

                    case PANEL: {
                        GUIPanel *innerPanel = getNode(component, GUIPanel, component);
                        innerPanel->component.position.x = innerPanel->component.position.x + container->component.position.x + container->component.padding.left + xOffset;
                        innerPanel->component.position.y = innerPanel->component.position.y + container->component.position.y + container->component.padding.top;
                        xOffset += innerPanel->component.size.width + innerPanel->component.margin.left + innerPanel->component.margin.right;
                        gui_panel_draw(innerPanel);
                        break;
                    }

                    case CONTAINER: {
                        GUIContainer *innerContainer = getNode(component, GUIContainer, component);
                        innerContainer->component.position.x = innerContainer->component.position.x + container->component.position.x + container->component.padding.left + xOffset;
                        innerContainer->component.position.y = innerContainer->component.position.y + container->component.position.y + container->component.padding.top;
                        xOffset += innerContainer->component.size.width + innerContainer->component.margin.left + innerContainer->component.margin.right;
                        gui_container_draw(innerContainer);
                        break;
                    }

                    default:
                        break;
                }
            }
        }
    }
}

void gui_container_draw(GUIContainer *container) {
    if (container->component.visable) {
        // 1. draw_background
        if (container->component.colorMode == RGB) {
            gfx2d_fill_rect(
                    container->component.position.x,
                    container->component.position.y,
                    container->component.position.x + container->component.size.width,
                    container->component.position.y + container->component.size.height,
                    container->component.background.r << 16 | container->component.background.g << 8 | container->component.background.b
            );
        }

        // 2. draw children
        gui_container_draw_children(container, container->orientation);
    }
}
