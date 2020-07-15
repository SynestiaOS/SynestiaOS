//
// Created by XingfengYang on 2020/7/7.
//

#include <framebuffer.h>
#include <mailbox.h>
#include <stdlib.h>

uint32_t pitch;
unsigned char *lfb;

uint32_t framebufferWidth;
uint32_t framebufferHeight;

int framebuffer_init(void) {
  mailbox[0] = 35 * 4;
  mailbox[1] = MBOX_REQUEST;

  mailbox[2] = 0x48003; // set phy wh
  mailbox[3] = 8;
  mailbox[4] = 8;
  mailbox[5] = 1024; // FrameBufferInfo.width
  mailbox[6] = 768;  // FrameBufferInfo.height

  mailbox[7] = 0x48004; // set virt wh
  mailbox[8] = 8;
  mailbox[9] = 8;
  mailbox[10] = 1024; // FrameBufferInfo.virtual_width
  mailbox[11] = 768;  // FrameBufferInfo.virtual_height

  mailbox[12] = 0x48009; // set virt offset
  mailbox[13] = 8;
  mailbox[14] = 8;
  mailbox[15] = 0; // FrameBufferInfo.x_offset
  mailbox[16] = 0; // FrameBufferInfo.y.offset

  mailbox[17] = 0x48005; // set depth
  mailbox[18] = 4;
  mailbox[19] = 4;
  mailbox[20] = 32; // FrameBufferInfo.depth

  mailbox[21] = 0x48006; // set pixel order
  mailbox[22] = 4;
  mailbox[23] = 4;
  mailbox[24] = 1; // RGB, not BGR preferably

  mailbox[25] = 0x40001; // get framebuffer, gets alignment on request
  mailbox[26] = 8;
  mailbox[27] = 8;
  mailbox[28] = 4096; // FrameBufferInfo.pointer
  mailbox[29] = 0;    // FrameBufferInfo.size

  mailbox[30] = 0x40008; // get pitch
  mailbox[31] = 4;
  mailbox[32] = 4;
  mailbox[33] = 0; // FrameBufferInfo.pitch

  mailbox[34] = MBOX_TAG_LAST;

  if (mailbox_call(MBOX_CH_PROP) && mailbox[20] == 32 && mailbox[28] != 0) {
    mailbox[28] &= 0x3FFFFFFF;
    framebufferWidth = mailbox[5];
    framebufferHeight = mailbox[6];
    pitch = mailbox[33];
    lfb = (void *)((uint64_t)mailbox[28]);
  } else {
    printf("[Framebuffer]: Unable to set screen resolution to 1024x768x32\n");
  }
}

void framebuffer_draw_pixel(uint32_t x, uint32_t y, char r, char g, char b) {
  unsigned char *ptr = lfb;
  uint32_t pixel;

  ptr += pitch * y;
  ptr += (x << 2);

  pixel = (b << 16) | (g << 8) | r;

  *((uint32_t *)ptr) = *((uint32_t *)&pixel);
}

void framebuffer_clear(uint32_t color) {
  unsigned char *ptr = lfb;
  // Clearing the whole screen
  for (uint32_t y = 0; y < framebufferHeight; y++) {
    for (uint32_t x = 0; x < framebufferWidth; x++) {
      *((uint32_t *)ptr) = color;
      ptr += 4;
    }
    ptr += pitch - framebufferWidth * 4;
  }
}
