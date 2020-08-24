//
// Created by XingfengYang on 2020/7/7.
//

#include <framebuffer.h>
#include <kheap.h>
#include <log.h>
#include <mailbox.h>

uint32_t pitch;
uint8_t *lfb;

uint32_t framebufferWidth;
uint32_t framebufferHeight;

uint32_t framebuffer_init(void) {
  PropertySetPhysicalDisplayWHMail *setPhysicalDisplayWHMail =
      kheap_alloc_aligned(sizeof(PropertySetPhysicalDisplayWHMail), 16);
  setPhysicalDisplayWHMail->size = sizeof(PropertySetPhysicalDisplayWHMail);
  setPhysicalDisplayWHMail->code = CODE_REQUEST;
  setPhysicalDisplayWHMail->end = PROPERTY_TAG_END;
  setPhysicalDisplayWHMail->property.tag = PROPERTY_TAG_SET_PHYSICAL_DISPLAY_WH;
  setPhysicalDisplayWHMail->property.bufferSize = 8;
  setPhysicalDisplayWHMail->property.code = 0x80000000 + 8;
  setPhysicalDisplayWHMail->property.width = 1024;
  setPhysicalDisplayWHMail->property.height = 768;
  MailMessage setPhysicalDisplayWHMailMsg = {.channel = MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC,
                                             .data = setPhysicalDisplayWHMail};
  mailbox_call(setPhysicalDisplayWHMailMsg);
  if (setPhysicalDisplayWHMail->code == CODE_RESPONSE_FAILURE ||
      setPhysicalDisplayWHMail->property.code == CODE_RESPONSE_FAILURE) {
    LogError("[Framebuffer]: Unable to set physical WH\n");
  }
  kheap_free(setPhysicalDisplayWHMail);

  PropertySetVirtualBufferWHMail *setVirtualBufferWHMail =
      kheap_alloc_aligned(sizeof(PropertySetVirtualBufferWHMail), 16);
  setVirtualBufferWHMail->size = sizeof(PropertySetVirtualBufferWHMail);
  setVirtualBufferWHMail->code = CODE_REQUEST;
  setVirtualBufferWHMail->end = PROPERTY_TAG_END;
  setVirtualBufferWHMail->property.tag = PROPERTY_TAG_SET_VIRTUAL_BUFFER_WH;
  setVirtualBufferWHMail->property.bufferSize = 8;
  setVirtualBufferWHMail->property.code = 0x80000000 + 8;
  setVirtualBufferWHMail->property.width = 1024;
  setVirtualBufferWHMail->property.height = 768;
  MailMessage setVirtualBufferWHMailMsg = {.channel = MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC,
                                           .data = setVirtualBufferWHMail};
  mailbox_call(setVirtualBufferWHMailMsg);
  if (setVirtualBufferWHMail->code == CODE_RESPONSE_FAILURE ||
      setVirtualBufferWHMail->property.code == CODE_RESPONSE_FAILURE) {
    LogError("[Framebuffer]: Unable to set virtual WH\n");
  }

  PropertySetDepthMail *setDepthMail = kheap_alloc_aligned(sizeof(PropertySetDepthMail), 16);
  setDepthMail->size = sizeof(PropertySetDepthMail);
  setDepthMail->code = CODE_REQUEST;
  setDepthMail->end = PROPERTY_TAG_END;
  setDepthMail->property.tag = PROPERTY_TAG_SET_DEPTH;
  setDepthMail->property.bufferSize = 4;
  setDepthMail->property.code = 0x80000000 + 4;
  setDepthMail->property.bitsPerPixel = 32;
  MailMessage setDepthMailMsg = {.channel = MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, .data = setDepthMail};
  mailbox_call(setDepthMailMsg);
  if (setDepthMail->code == CODE_RESPONSE_FAILURE || setDepthMail->property.code == CODE_RESPONSE_FAILURE) {
    LogError("[Framebuffer]: Unable to set depth\n");
  }

  PropertySetVirtualOffsetMail *setVirtualOffsetMail = kheap_alloc_aligned(sizeof(PropertySetVirtualOffsetMail), 16);
  setVirtualOffsetMail->size = sizeof(PropertySetVirtualOffsetMail);
  setVirtualOffsetMail->code = CODE_REQUEST;
  setVirtualOffsetMail->end = PROPERTY_TAG_END;
  setVirtualOffsetMail->property.tag = PROPERTY_TAG_SET_VIRTUAL_OFFSET;
  setVirtualOffsetMail->property.bufferSize = 8;
  setVirtualOffsetMail->property.code = 0x80000000 + 8;
  setVirtualOffsetMail->property.xOffset = 0;
  setVirtualOffsetMail->property.yOffset = 0;
  MailMessage setVirtualOffsetMailMsg = {.channel = MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC,
                                         .data = setVirtualOffsetMail};
  mailbox_call(setVirtualOffsetMailMsg);
  if (setVirtualOffsetMail->code == CODE_RESPONSE_FAILURE ||
      setVirtualOffsetMail->property.code == CODE_RESPONSE_FAILURE) {
    LogError("[Framebuffer]: Unable to set virtual offset\n");
  }

  PropertyAllocateBufferMail *allocateBufferMail = kheap_alloc_aligned(sizeof(PropertyAllocateBufferMail), 16);
  allocateBufferMail->size = sizeof(PropertyAllocateBufferMail);
  allocateBufferMail->code = CODE_REQUEST;
  allocateBufferMail->end = PROPERTY_TAG_END;
  allocateBufferMail->property.tag = PROPERTY_TAG_ALLOCATE_BUFFER;
  allocateBufferMail->property.bufferSize = 8;
  allocateBufferMail->property.code = 0x80000000 + 4;
  allocateBufferMail->property.PACKED.alignment = 16;
  allocateBufferMail->property.size = 0;
  MailMessage allocateBufferMailMsg = {.channel = MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, .data = allocateBufferMail};
  mailbox_call(allocateBufferMailMsg);
  if (allocateBufferMail->code == CODE_RESPONSE_FAILURE || allocateBufferMail->property.code == CODE_RESPONSE_FAILURE) {
    LogError("[Framebuffer]: Unable to allocate video buffer\n");
  }

  PropertyGetPitchMail *getPitchMail = kheap_alloc_aligned(sizeof(PropertyGetPitchMail), 16);
  getPitchMail->size = sizeof(PropertyGetPitchMail);
  getPitchMail->code = CODE_REQUEST;
  getPitchMail->end = PROPERTY_TAG_END;
  getPitchMail->property.tag = PROPERTY_TAG_GET_PITCH;
  getPitchMail->property.bufferSize = 4;
  getPitchMail->property.code = 0;
  getPitchMail->property.bytesPerLine = 0;
  MailMessage getPitchMailMsg = {.channel = MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, .data = getPitchMail};
  mailbox_call(getPitchMailMsg);
  if (getPitchMail->code == CODE_RESPONSE_FAILURE || getPitchMail->property.code == CODE_RESPONSE_FAILURE) {
    LogError("[Framebuffer]: Unable to get pitch\n");
  }

  if (setDepthMail->property.bitsPerPixel == 32 && allocateBufferMail->property.PACKED.baseAddress != 0) {
    allocateBufferMail->property.PACKED.baseAddress &= 0x3FFFFFFF;
    framebufferWidth = setPhysicalDisplayWHMail->property.width;
    framebufferHeight = setPhysicalDisplayWHMail->property.height;
    pitch = getPitchMail->property.bytesPerLine;
    lfb = (void *)((uint64_t)allocateBufferMail->property.PACKED.baseAddress);
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
