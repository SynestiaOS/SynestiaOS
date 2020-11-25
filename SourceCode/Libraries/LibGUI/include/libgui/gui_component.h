//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_COMPONENT_H__
#define __LIBRARY_LIBGUI_COMPONENT_H__

#include <kernel/list.h>
#include <stdbool.h>
#include <libc/stdint.h>

#define DEFAULT_FONT_SIZE 8
#define DEFAULT_PADDING 8
#define DEFAULT_MARGIN 0

#define DEFAULT_WINDOW_HEADER_HEIGHT DEFAULT_FONT_SIZE + 4 * DEFAULT_PADDING

typedef struct Position {
    uint32_t x;
    uint32_t y;
} Position;

Position PositionXY(uint32_t x, uint32_t y);

typedef struct Size {
    uint32_t width;
    uint32_t height;
} Size;

Size SizeWH(uint32_t width, uint32_t height);

typedef struct Padding {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
} Padding;

Padding Padding4(uint32_t left,
                 uint32_t right,
                 uint32_t top,
                 uint32_t bottom);

typedef struct Margin {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
} Margin;

Margin Margin4(uint32_t left,
               uint32_t right,
               uint32_t top,
               uint32_t bottom);

typedef struct Color {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

Color ColorARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

Color ColorRGB(uint8_t r, uint8_t g, uint8_t b);

typedef struct Pixel {
    Position pos;
    Color color;
} Pixel;

Pixel Pixel2D(Position pos, Color c);

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

BoxShadow Shadow(Color color, uint32_t width);

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
#endif//__LIBRARY_LIBGUI_COMPONENT_H__
