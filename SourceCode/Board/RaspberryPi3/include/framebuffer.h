//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP3_FRAMEBUFFER_H__
#define __BOARD_RASP3_FRAMEBUFFER_H__

#include <stdint.h>

#define COLORDEPTH 24
#define BYTES_PER_PIXEL COLORDEPTH / 8

typedef struct psf_t {
  uint32_t magic;
  uint32_t version;
  uint32_t headersize;
  uint32_t flags;
  uint32_t numglyph;
  uint32_t bytesperglyph;
  uint32_t height;
  uint32_t width;
  unsigned char glyphs;
} __attribute__((packed)) psf_t;

extern volatile unsigned char _binary_src_font_font_psf_start;

int framebuffer_init(void);

void framebuffer_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b);

void framebuffer_clear(uint32_t color);

#endif //__BOARD_RASP3_FRAMEBUFFER_H__
