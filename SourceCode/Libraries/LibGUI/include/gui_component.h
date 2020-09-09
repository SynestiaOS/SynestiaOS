//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_COMPONENT_H__
#define __LIBRARY_LIBGUI_COMPONENT_H__

#include <list.h>
#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_FONT_SIZE 8
#define DEFAULT_PADDING 8
#define DEFAULT_MARGIN 0

#define DEFAULT_WINDOW_HEADER_HEIGHT DEFAULT_FONT_SIZE + 4 * DEFAULT_PADDING

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

typedef struct Pixel {
    Position pos;
    Color color;
} Pixel;

typedef enum ComponentType {
    BUTTON,
    LABEL,
    WINDOW,
    PANEL,
    CONTAINER,
    CANVAS,
    VIEW3D,
} ComponentType;

typedef enum ColorMode {
    TRANSPARENT,
    RGB,
} ColorMode;

typedef struct BoxShadow {
    bool enable;
    Color color;
    uint32_t width;
} BoxShadow;

typedef struct GUIComponent {
    ComponentType type;
    bool visable;
    ColorMode colorMode;
    ListNode node;
    Position position;
    Size size;
    Color background;
    Color foreground;
    Padding padding;
    Margin margin;
    BoxShadow boxShadow;
} GUIComponent;
#endif //__LIBRARY_LIBGUI_COMPONENT_H__
