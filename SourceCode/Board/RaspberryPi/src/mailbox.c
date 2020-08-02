//
// Created by XingfengYang on 2020/7/7.
//

#include <mailbox.h>
#include <stdbool.h>
#include <stdlib.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

#define VIDEOCORE_MBOX PERIPHERAL_BASE + MAILBOX_OFFSET


#define MAILBOX_CHANNEL_POWER_MANAGEMENT 0
#define MAILBOX_CHANNEL_FRAMEBUFFER 1
#define MAILBOX_CHANNEL_VIRTUAL_UART 2
#define MAILBOX_CHANNEL_VCHIQ 3
#define MAILBOX_CHANNEL_LEDS 4
#define MAILBOX_CHANNEL_BUTTONS 5
#define MAILBOX_CHANNEL_TOUCH_SCREEN 6

/**
 * The read register for mailbox 0 at offset (the Linux source mentions something of "and the next 4 words", but I've found it sufficient to read only from this address)
 * 0-3(channel):	The mailbox channel number from which the data originated
 * 4-31(data):	The 28 bits of data sent to the CPU
 */
#define MAIL0_READ ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x0))

// Read from the mailbox without removing data from it.
#define MAIL0_PEAK ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x10))

// Sender ID (bottom 2 bits only)
#define MAIL0_SENDER ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x14))

/**
 * The status register for mailbox 0
 * 0-29:	N/A	Not documented here. Unused?
 * 30:	MAIL_EMPTY	Set if the mailbox is empty, and thus no more data is available to be read from it.
 * 31:	MAIL_FULL	Set if the mailbox is full, and thus no more data can be written to it.
 */
#define MAIL0_STATUS ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x18))

// The configuration register for mailbox 0
#define MAIL0_CONFIG ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x1C))

/**
 *  The write register for mailbox 0 (this is actually the read register for mailbox 1).
 *  0-3:	channel	The mailbox channel number to which the data is to be sent
 *  4-31:	data	The 28 bits of data to be sent to the destination
 */
#define MAIL0_WRITE ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x20))

#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 1<<31
#define MBOX_EMPTY 1<<30

struct __attribute__((__packed__, aligned(4))) mbox_registers {
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
};

_Static_assert((sizeof(struct mbox_registers) == 0x40), "Structure MailBoxRegisters should be 0x40 bytes in size");

#define MAILBOX_FOR_READ_WRITES                                                                                        \
  ((volatile __attribute__((aligned(4))) struct mbox_registers *)(uint32_t *)(PERIPHERAL_BASE + 0xB880))

/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int32_t mailbox_call(uint8_t ch) {
  uint32_t r;
  /* wait until we can write to the mailbox */
  do {
    asm volatile("nop");
  } while (*MAIL0_STATUS & MBOX_FULL);
  /* write the address of our message to the mailbox with channel identifier */
  *MAIL0_WRITE = (((uint32_t)((uint64_t)&mailbox) & ~0xF) | (ch & 0xF));
  /* now wait for the response */
  while (1) {
    /* is there a response? */
    do {
      asm volatile("nop");
    } while (*MAIL0_STATUS & MBOX_EMPTY);
    r = *MAIL0_READ;
    /* is it a response to our message? */
    if ((unsigned char)(r & 0xF) == ch && (r & ~0xF) == (uint32_t)((uint64_t)&mailbox))
      /* is it a valid successful response? */
      return mailbox[1] == MBOX_RESPONSE;
  }
  return 0;
}