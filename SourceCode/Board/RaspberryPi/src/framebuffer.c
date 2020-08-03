//
// Created by XingfengYang on 2020/7/7.
//

#include <framebuffer.h>
#include <kheap.h>
#include <log.h>
#include <mailbox.h>
#include <stdlib.h>

uint32_t pitch;
unsigned char *lfb;

uint32_t framebufferWidth;
uint32_t framebufferHeight;

int framebuffer_init(void) {
  PropertySetPhysicalDisplayWHMail *setPhysicalDisplayWHMail =
      kheap_alloc_aligned(sizeof(PropertySetPhysicalDisplayWHMail), 16);
  setPhysicalDisplayWHMail->size = sizeof(PropertySetPhysicalDisplayWHMail);
  setPhysicalDisplayWHMail->tag = MBOX_REQUEST;
  setPhysicalDisplayWHMail->end = PROPERTY_TAG_END;
  setPhysicalDisplayWHMail->property.tag = PROPERTY_TAG_SET_PHYSICAL_DISPLAY_WH;
  setPhysicalDisplayWHMail->property.reqSize = 8;
  setPhysicalDisplayWHMail->property.rspSize = 8;
  setPhysicalDisplayWHMail->property.width = 1024;
  setPhysicalDisplayWHMail->property.width = 768;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)setPhysicalDisplayWHMail);

  PropertySetVirtualBufferWHMail *setVirtualBufferWHMail =
      kheap_alloc_aligned(sizeof(PropertySetVirtualBufferWHMail), 16);
  setVirtualBufferWHMail->size = sizeof(PropertySetVirtualBufferWHMail);
  setVirtualBufferWHMail->tag = MBOX_REQUEST;
  setVirtualBufferWHMail->end = PROPERTY_TAG_END;
  setVirtualBufferWHMail->property.tag = PROPERTY_TAG_SET_VIRTUAL_BUFFER_WH;
  setVirtualBufferWHMail->property.reqSize = 8;
  setVirtualBufferWHMail->property.rspSize = 8;
  setVirtualBufferWHMail->property.width = 1024;
  setVirtualBufferWHMail->property.width = 768;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)setVirtualBufferWHMail);

  PropertySetVirtualOffsetMail *setVirtualOffsetMail = kheap_alloc_aligned(sizeof(PropertySetVirtualOffsetMail), 16);
  setVirtualOffsetMail->size = sizeof(PropertySetVirtualOffsetMail);
  setVirtualOffsetMail->tag = MBOX_REQUEST;
  setVirtualOffsetMail->end = PROPERTY_TAG_END;
  setVirtualOffsetMail->property.tag = PROPERTY_TAG_SET_VIRTUAL_OFFSET;
  setVirtualOffsetMail->property.reqSize = 8;
  setVirtualOffsetMail->property.rspSize = 8;
  setVirtualOffsetMail->property.xOffset = 0;
  setVirtualOffsetMail->property.yOffset = 0;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)setVirtualOffsetMail);

  PropertySetDepthMail *setDepthMail = kheap_alloc_aligned(sizeof(PropertySetDepthMail), 16);
  setDepthMail->size = sizeof(PropertySetDepthMail);
  setDepthMail->tag = MBOX_REQUEST;
  setDepthMail->end = PROPERTY_TAG_END;
  setDepthMail->property.tag = PROPERTY_TAG_SET_DEPTH;
  setDepthMail->property.reqSize = 4;
  setDepthMail->property.rspSize = 4;
  setDepthMail->property.bitsPerPixel = 32;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)setDepthMail);

  PropertySetPixelOrderMail *setPixelOrderMail = kheap_alloc_aligned(sizeof(PropertySetPixelOrderMail), 16);
  setPixelOrderMail->size = sizeof(PropertySetPixelOrderMail);
  setPixelOrderMail->tag = MBOX_REQUEST;
  setPixelOrderMail->end = PROPERTY_TAG_END;
  setPixelOrderMail->property.tag = PROPERTY_TAG_SET_PIXEL_ORDER;
  setPixelOrderMail->property.reqSize = 4;
  setPixelOrderMail->property.rspSize = 4;
  setPixelOrderMail->property.state = 1;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)setPixelOrderMail);

  PropertyAllocateBufferMail *allocateBufferMail = kheap_alloc_aligned(sizeof(PropertyAllocateBufferMail), 16);
  allocateBufferMail->size = sizeof(PropertyAllocateBufferMail);
  allocateBufferMail->tag = MBOX_REQUEST;
  allocateBufferMail->end = PROPERTY_TAG_END;
  allocateBufferMail->property.tag = PROPERTY_TAG_ALLOCATE_BUFFER;
  allocateBufferMail->property.reqSize = 8;
  allocateBufferMail->property.rspSize = 8;
  allocateBufferMail->property.baseAddress = 4096;
  allocateBufferMail->property.size = 0;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)allocateBufferMail);

  PropertyGetPitchMail *getPitchMail = kheap_alloc_aligned(sizeof(PropertyGetPitchMail), 16);
  getPitchMail->size = sizeof(PropertyGetPitchMail);
  getPitchMail->tag = MBOX_REQUEST;
  getPitchMail->end = PROPERTY_TAG_END;
  getPitchMail->property.tag = PROPERTY_TAG_GET_PITCH;
  getPitchMail->property.reqSize = 4;
  getPitchMail->property.rspSize = 4;
  getPitchMail->property.bytesPerLine = 0;
  mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)getPitchMail);

  if (setDepthMail->property.bitsPerPixel == 32 && allocateBufferMail->property.baseAddress != 0) {
    allocateBufferMail->property.baseAddress &= 0x3FFFFFFF;
    framebufferWidth = setPhysicalDisplayWHMail->property.width;
    framebufferHeight = setPhysicalDisplayWHMail->property.height;
    pitch = getPitchMail->property.bytesPerLine;
    lfb = (void *)((uint64_t)allocateBufferMail->property.baseAddress);
  } else {
    LogError("[Framebuffer]: Unable to set screen resolution to 1024x768x32\n");
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
