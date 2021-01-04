//
// Created by XingfengYang on 2020/12/19.
//

#ifndef SYNESTIAOS_BMP_H
#define SYNESTIAOS_BMP_H

#include "libc/stdint.h"

typedef struct BmpFileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetOfData;
} BmpFileHeader;

typedef struct BitmapInformation {
    uint32_t infoSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitCounts;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPixelsPerMeter;
    uint32_t yPixelsPerMeter;
    uint32_t clrUsed;
    uint32_t clrImportant;
} BitmapInformation;

typedef struct BitmapColorPalette {

} BitmapColorPalette;

typedef struct Bmp {
    BmpFileHeader header;
    BitmapInformation info;
    BitmapColorPalette palette;
    char *data;
} Bmp;

#endif//SYNESTIAOS_BMP_H
