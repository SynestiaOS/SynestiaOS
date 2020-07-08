//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_COMPONENT_H__
#define __LIBRARY_LIBGUI_COMPONENT_H__

#include <stdint.h>
#include <list.h>

#define DEFAULT_FONT_SIZE 8
#define DEFAULT_PADDING 8
#define DEFAULT_MARGIN 0

#define DEFAULT_WINDOW_HEADER_HEIGHT  DEFAULT_FONT_SIZE+2*DEFAULT_PADDING

typedef struct Position {
    uint32_t x;
    uint32_t y;
} Position;

typedef struct Size {
    uint32_t width;
    uint32_t height;
} Size;

typedef struct Padding {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
} Padding;

typedef struct Margin {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
} Margin;


typedef struct Color {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef enum ComponentType {
    BUTTON,
    LABEL,
    WINDOW,
    PANEL,
    CONTAINER,
} ComponentType;

typedef struct GUIComponent {
    ComponentType type;
    bool visable;
    ListNode node;
    Position position;
    Size size;
    Color background;
    Color foreground;
    Padding padding;
    Margin margin;
} GUIComponent;
#endif //__LIBRARY_LIBGUI_COMPONENT_H__
