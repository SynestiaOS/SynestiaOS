//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_COMPONENT_H__
#define __LIBRARY_LIBGUI_COMPONENT_H__

#include <stdint.h>

typedef struct Position {
    uint32_t x;
    uint32_t y;
} Position;

typedef struct Size {
    uint32_t width;
    uint32_t height;
} Size;


typedef struct Color {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct GUIComponent {
    Position position;
    Size size;
    Color background;
    Color foreground;
} CUIComponent;
#endif //__LIBRARY_LIBGUI_COMPONENT_H__
