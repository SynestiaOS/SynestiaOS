//
// Created by XingfengYang on 2020/7/7.
//

#include <gui_window.h>
#include <gfx2d.h>
#include <gui_button.h>
#include <gui_label.h>
#include <stdbool.h>
#include <gui_panel.h>
#include <gui_container.h>
#include <stdlib.h>

void gui_window_create(GUIWindow *window) {
    window->component.type = WINDOW;
    window->component.visable = true;
    window->component.colorMode = RGB;
    window->component.node.next = nullptr;
    window->component.node.prev = nullptr;
    window->children = nullptr;

    window->component.position.x = 0;
    window->component.position.y = 0;

    window->component.size.height = 0;
    window->component.size.width = 0;

    window->component.padding.top = 0;
    window->component.padding.bottom = 0;
    window->component.padding.left = 0;
    window->component.padding.right = 0;

    window->component.margin.top = 0;
    window->component.margin.bottom = 0;
    window->component.margin.left = 0;
    window->component.margin.right = 0;

    window->component.background.a = 0x00;
    window->component.background.r = 0xFF;
    window->component.background.g = 0xFF;
    window->component.background.b = 0xFF;

    window->component.foreground.a = 0x00;
    window->component.foreground.r = 0x00;
    window->component.foreground.g = 0x00;
    window->component.foreground.b = 0x00;

    window->title = "";

    window->children = kvector_allocate();
    if (window->children == nullptr) {
        printf("[GUI]: window create failed, unable to allocate children vector\n");
    }
}

void gui_window_init(GUIWindow *window, uint32_t x, uint32_t y, const char *title) {
    window->component.position.x = x;
    window->component.position.y = y;

    window->component.padding.top = (window->component.padding.top == 0 ? DEFAULT_PADDING : window->component.padding.top);
    window->component.padding.bottom = (window->component.padding.bottom == 0 ? DEFAULT_PADDING : window->component.padding.bottom);
    window->component.padding.left = (window->component.padding.left == 0 ? DEFAULT_PADDING : window->component.padding.left);
    window->component.padding.right = (window->component.padding.right == 0 ? DEFAULT_PADDING : window->component.padding.right);

    window->component.margin.top = (window->component.margin.top == 0 ? DEFAULT_MARGIN : window->component.margin.top);
    window->component.margin.bottom = (window->component.margin.bottom == 0 ? DEFAULT_MARGIN : window->component.margin.bottom);
    window->component.margin.left = (window->component.margin.left == 0 ? DEFAULT_MARGIN : window->component.margin.left);
    window->component.margin.right = (window->component.margin.right == 0 ? DEFAULT_MARGIN : window->component.margin.right);

    window->title = title;

    char *tmp = title;
    uint32_t length = 0;
    while (*tmp) {
        length++;
        tmp++;
    }

    if (window->component.size.width == 0) {
        window->component.size.width = DEFAULT_WINDOW_WIDTH;

    }
    if (window->component.size.height == 0) {
        window->component.size.height = DEFAULT_WINDOW_HEIGHT;
    }
}

void gui_window_add_children(GUIWindow *window, GUIComponent *component) {
    if (window->children == nullptr) {
        window->children = component;
    } else {
        kvector_add(window->children, &component->node);
    }
}

void gui_window_draw(GUIWindow *window) {
    if (window->component.visable) {
        if (window->component.colorMode == RGB) {
            // 1. draw_background
            gfx2d_fill_rect(
                    window->component.position.x,
                    window->component.position.y,
                    window->component.position.x + window->component.size.width,
                    window->component.position.y + window->component.size.height + DEFAULT_WINDOW_HEADER_HEIGHT,
                    window->component.background.r << 16 | window->component.background.g << 8 | window->component.background.b
            );
        }

        // 2. draw header
        gfx2d_fill_rect(
                window->component.position.x,
                window->component.position.y,
                window->component.position.x + window->component.size.width,
                window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT,
                FLUENT_PRIMARY_COLOR
        );

        // 3. draw_font
        char *tmp = window->title;
        uint32_t xOffset = 0;
        while (*tmp) {
            gfx2d_draw_ascii(
                    window->component.position.x + xOffset * DEFAULT_FONT_SIZE + DEFAULT_PADDING,
                    window->component.position.y + DEFAULT_PADDING,
                    *tmp,
                    0xFFFFFF
            );
            xOffset++;
            tmp++;
        }

        // 4. draw header window
        gfx2d_draw_rect(
                window->component.position.x + window->component.size.width - 24 * 3,
                window->component.position.y + 4,
                window->component.position.x + window->component.size.width - 24 * 3 + 16,
                window->component.position.y + 4 + 16,
                0x00FFFFFF
        );
        gfx2d_draw_ascii(window->component.position.x + window->component.size.width - 24 * 3 + 4,
                         window->component.position.y + 4 + 4, '_', 0xFFFFFF);
        gfx2d_draw_rect(
                window->component.position.x + window->component.size.width - 24 * 2,
                window->component.position.y + 4,
                window->component.position.x + window->component.size.width - 24 * 2 + 16,
                window->component.position.y + 4 + 16,
                0x00FFFFFF
        );
        gfx2d_draw_ascii(window->component.position.x + window->component.size.width - 24 * 2 + 4,
                         window->component.position.y + 4 + 4, '#', 0xFFFFFF);

        gfx2d_draw_rect(
                window->component.position.x + window->component.size.width - 24 * 1,
                window->component.position.y + 4,
                window->component.position.x + window->component.size.width - 24 * 1 + 16,
                window->component.position.y + 4 + 16,
                0x00FFFFFF
        );
        gfx2d_draw_ascii(window->component.position.x + window->component.size.width - 24 * 1 + 4,
                         window->component.position.y + 4 + 4, 'x', 0xFFFFFF);

        // 5. draw border
        gfx2d_draw_rect(
                window->component.position.x,
                window->component.position.y,
                window->component.position.x + window->component.size.width,
                window->component.position.y + window->component.size.height + DEFAULT_WINDOW_HEADER_HEIGHT,
                FLUENT_PRIMARY_COLOR
        );

        // 6. draw children
        gui_window_draw_children(window);

        // 7. register click event

        // 7. register drag event
    }
}

void gui_window_draw_children(GUIWindow *window) {
    KernelVector *children = window->children;

    if (children != nullptr) {
        for (uint32_t i = 0; i < children->index; i++) {
            ListNode *listNode = children->node[i];
            GUIComponent *component = getNode(listNode, GUIComponent, node);
            switch (component->type) {
                case BUTTON: {
                    GUIButton *button = getNode(component, GUIButton, component);
                    button->component.position.x = button->component.position.x + window->component.position.x + window->component.padding.left;
                    button->component.position.y = button->component.position.y + window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
                    gui_button_draw(button);
                    break;
                }

                case LABEL: {
                    GUILabel *label = getNode(component, GUILabel, component);
                    label->component.position.x = label->component.position.x + window->component.position.x + window->component.padding.left;
                    label->component.position.y = label->component.position.y + window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
                    gui_label_draw(label);
                    break;
                }

                case PANEL: {
                    GUIPanel *innerPanel = getNode(component, GUIPanel, component);
                    innerPanel->component.position.x = innerPanel->component.position.x + window->component.position.x + window->component.padding.left;
                    innerPanel->component.position.y =
                            innerPanel->component.position.y + window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
                    gui_panel_draw(innerPanel);
                    break;
                }

                case CONTAINER: {
                    GUIContainer *innerContainer = getNode(component, GUIContainer, component);
                    innerContainer->component.position.x = innerContainer->component.position.x + window->component.position.x + window->component.padding.left;
                    innerContainer->component.position.y =
                            innerContainer->component.position.y + window->component.position.y + DEFAULT_WINDOW_HEADER_HEIGHT + window->component.padding.top;
                    gui_container_draw(innerContainer);
                    break;
                }
                default:
                    break;
            }
        }
    }
}
