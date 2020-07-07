//
// Created by XingfengYang on 2020/7/7.
//

#include <mailbox.h>
#include <stdlib.h>
#include <stdbool.h>

volatile uint32_t  __attribute__((aligned(16))) mailbox[36];

#define VIDEOCORE_MBOX  PERIPHERAL_BASE + MAILBOX_OFFSET
#define MBOX_READ       ((volatile uint32_t*)(VIDEOCORE_MBOX+0x0))
#define MBOX_POLL       ((volatile uint32_t*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SENDER     ((volatile uint32_t*)(VIDEOCORE_MBOX+0x14))
#define MBOX_STATUS     ((volatile uint32_t*)(VIDEOCORE_MBOX+0x18))
#define MBOX_CONFIG     ((volatile uint32_t*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRITE      ((volatile uint32_t*)(VIDEOCORE_MBOX+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

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

#define MAILBOX_FOR_READ_WRITES ((volatile __attribute__((aligned(4))) struct mbox_registers*)(uint32_t *)(PERIPHERAL_BASE + 0xB880))

/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int32_t mailbox_call(uint8_t ch) {
    uint32_t r;
    /* wait until we can write to the mailbox */
    do { asm volatile("nop"); } while (*MBOX_STATUS & MBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MBOX_WRITE = (((uint32_t) ((uint64_t) &mailbox) & ~0xF) | (ch & 0xF));
    /* now wait for the response */
    while (1) {
        /* is there a response? */
        do { asm volatile("nop"); } while (*MBOX_STATUS & MBOX_EMPTY);
        r = *MBOX_READ;
        /* is it a response to our message? */
        if ((unsigned char) (r & 0xF) == ch && (r & ~0xF) == (uint32_t) ((uint64_t) &mailbox))
            /* is it a valid successful response? */
            return mailbox[1] == MBOX_RESPONSE;
    }
    return 0;
}

bool mailbox_tag_write(uint32_t message) {
    uint32_t value;    // Temporary read value
    message &= ~(0xF); // Make sure 4 low channel bits are clear
    message |= 0x8; // OR the channel bits to the value
    do {
        value = MAILBOX_FOR_READ_WRITES->status_1; // Read mailbox1 status from GPU
    } while ((value & MAIL_FULL) != 0); // Make sure arm mailbox is not full
    MAILBOX_FOR_READ_WRITES->write_1 = message; // Write value to mailbox
    return true; // Write success
}

uint32_t mailbox_tag_read() {
    uint32_t value;    // Temporary read value
    do {
        do {
            value = MAILBOX_FOR_READ_WRITES->status_0; // Read mailbox0 status
        } while ((value & MAIL_EMPTY) != 0); // Wait for data in mailbox
        value = MAILBOX_FOR_READ_WRITES->read_0; // Read the mailbox
    } while ((value & 0xF) != 0x8); // We have response back
    value &= ~(0xF); // Lower 4 low channel bits are not part of message
    return value; // Return the value
}
