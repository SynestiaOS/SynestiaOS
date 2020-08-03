//
// Created by XingfengYang on 2020/7/7.
//

#include <mailbox.h>
#include <stdbool.h>
#include <stdlib.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

struct mbox_registers {
  const volatile uint32_t read_0; // 0x00         Read data from VC to ARM
  uint32_t unused[3];             // 0x04-0x0F
  volatile uint32_t peek_0;       // 0x10
  volatile uint32_t sender_0;     // 0x14
  volatile uint32_t status_0;     // 0x18         Status of VC to ARM
  volatile uint32_t config0;      // 0x1C
  volatile uint32_t write_1;      // 0x20         Write data from ARM to VC
  uint32_t unused_2[3];           // 0x24-0x2F
  volatile uint32_t peek_1;       // 0x30
  volatile uint32_t sender_1;     // 0x34
  volatile uint32_t status_1;     // 0x38         Status of ARM to VC
  volatile uint32_t config_1;     // 0x3C
} __attribute__((__packed__, aligned(4)));

uint32_t mailbox_call(uint8_t channel, uint32_t mailbox) {
  mailbox_write(channel, mailbox);
  uint32_t data = mailbox_read(channel);
  return data;
}

uint32_t mailbox_read(uint8_t channel) {
  // Loop until we receive something from the requested channel
  for (;;) {
    while ((*(uint32_t *)(MAIL0_STATUS)&MBOX_EMPTY) != 0) {
      // Wait for data
    }
    // Read the data
    uint32_t data = *(uint32_t *)(MAIL0_READ);
    uint32_t readChannel = data & 0xF;
    data >>= 4;
    // Return it straight away if it's for the requested channel
    if (readChannel == channel) {
      return data;
    }
  }
}

void mailbox_write(uint8_t channel, uint32_t data) {
  while ((*(uint32_t *)(MAIL0_STATUS)&MBOX_FULL) != 0) {
    // Wait for data
  }
  // Write the value to the requested channel
  *(uint32_t *)(MAIL0_WRITE) = ((data & ~0xF) | channel);
}
