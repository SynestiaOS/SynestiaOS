//
// Created by XingfengYang on 2020/7/7.
//

#include <mailbox.h>
#include <stdbool.h>
#include <stdlib.h>

uint32_t mailbox_call(uint8_t channel, uint32_t mailbox) {
  while (!((*(uint32_t *)(MAIL0_STATUS)) & MBOX_EMPTY)) {
    *(uint32_t *)(MAIL0_READ);
  }
  mailbox_write(channel, mailbox);
  uint32_t data = mailbox_read(channel);
  return data;
}

uint32_t mailbox_read(uint8_t channel) {
  // Loop until we receive something from the requested channel
  uint32_t data;
  do {
    while ((*(uint32_t *)(MAIL0_STATUS)) & MBOX_EMPTY) {
      // Wait for data
    }
    data = *(uint32_t *)(MAIL0_READ);
  } while ((data & 0xF) != channel);
  return data & ~0xF;
}

void mailbox_write(uint8_t channel, uint32_t data) {
  while ((*(uint32_t *)(MAIL0_STATUS)) & MBOX_FULL) {
    // Wait for data
  }
  // Write the value to the requested channel
  *(uint32_t *)(MAIL0_WRITE) = (data | channel);
}
