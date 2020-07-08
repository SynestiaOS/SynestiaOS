//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGUI_COMPONENT_H__
#define __LIBRARY_LIBGUI_COMPONENT_H__

#include <stdint.h>

#define DEFAULT_FONT_SIZE 8
#define DEFAULT_pADDING 8
#define DEFAULT_MARGIN 0

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

typedef struct GUIComponent {
    Position position;
    Size size;
    Color background;
    Color foreground;
    Padding padding;
    Margin margin;
} CUIComponent;
#endif //__LIBRARY_LIBGUI_COMPONENT_H__
