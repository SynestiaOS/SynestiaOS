//
// Created by XingfengYang on 2020/7/7.
//

#include "libgui/gui_component.h"

Position PositionXY(uint32_t x, uint32_t y) {
    Position p = {x, y};
    return p;
}

Size SizeWH(uint32_t width, uint32_t height) {
    Size s = {width, height};
    return s;
}

Color ColorARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    Color c = {
            a, r, g, b};
    return c;
}

Color ColorRGB(uint8_t r, uint8_t g, uint8_t b) {
    return ColorARGB(0, r, g, b);
}


Padding Padding4(uint32_t left,
                 uint32_t right,
                 uint32_t top,
                 uint32_t bottom) {
    Padding p = {
            left, right, top, bottom};
    return p;
}

Margin Margin4(uint32_t left,
               uint32_t right,
               uint32_t top,
               uint32_t bottom) {
    Margin m = {
            left, right, top, bottom};
    return m;
}

Pixel Pixel2D(Position pos, Color c) {
    Pixel p = {pos, c};
    return p;
}
