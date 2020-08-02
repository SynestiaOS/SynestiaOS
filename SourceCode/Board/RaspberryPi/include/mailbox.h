//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP_MAILBOX_H__
#define __BOARD_RASP_MAILBOX_H__

#include <raspi.h>
#include <stdbool.h>
#include <stdint.h>

extern volatile uint32_t __attribute__((aligned(16))) mailbox[36];
#define VIDEOCORE_MBOX PERIPHERAL_BASE + MAILBOX_OFFSET

#define PROPTAG_END			0x00000000
#define PROPTAG_GET_FIRMWARE_REVISION	0x00000001
#define PROPTAG_SET_CURSOR_INFO		0x00008010
#define PROPTAG_SET_CURSOR_STATE	0x00008011
#define PROPTAG_GET_BOARD_MODEL		0x00010001
#define PROPTAG_GET_BOARD_REVISION	0x00010002
#define PROPTAG_GET_MAC_ADDRESS		0x00010003
#define PROPTAG_GET_BOARD_SERIAL	0x00010004
#define PROPTAG_GET_ARM_MEMORY		0x00010005
#define PROPTAG_GET_VC_MEMORY		0x00010006
#define PROPTAG_SET_POWER_STATE		0x00028001
#define PROPTAG_GET_CLOCK_RATE		0x00030002
#define PROPTAG_GET_MAX_CLOCK_RATE	0x00030004
#define PROPTAG_GET_TEMPERATURE		0x00030006
#define PROPTAG_GET_MIN_CLOCK_RATE	0x00030007
#define PROPTAG_GET_TURBO		0x00030009
#define PROPTAG_GET_MAX_TEMPERATURE	0x0003000A
#define PROPTAG_GET_EDID_BLOCK		0x00030020
#define PROPTAG_SET_CLOCK_RATE		0x00038002
#define PROPTAG_SET_TURBO		0x00038009
#define PROPTAG_SET_SET_GPIO_STATE	0x00038041
#define PROPTAG_ALLOCATE_BUFFER		0x00040001
#define PROPTAG_GET_DISPLAY_DIMENSIONS	0x00040003
#define PROPTAG_GET_PITCH		0x00040008
#define PROPTAG_GET_TOUCHBUF		0x0004000F
#define PROPTAG_GET_GPIO_VIRTBUF	0x00040010
#define PROPTAG_SET_PHYS_WIDTH_HEIGHT	0x00048003
#define PROPTAG_SET_VIRT_WIDTH_HEIGHT	0x00048004
#define PROPTAG_SET_DEPTH		0x00048005
#define PROPTAG_SET_VIRTUAL_OFFSET	0x00048009
#define PROPTAG_SET_PALETTE		0x0004800B
#define PROPTAG_WAIT_FOR_VSYNC		0x0004800E
#define PROPTAG_SET_BACKLIGHT		0x0004800F
#define PROPTAG_SET_TOUCHBUF		0x0004801F
#define PROPTAG_SET_GPIO_VIRTBUF	0x00048020
#define PROPTAG_GET_COMMAND_LINE	0x00050001
#define PROPTAG_GET_DMA_CHANNELS	0x00060001

#define MAILBOX_CHANNEL_POWER_MANAGEMENT 0
#define MAILBOX_CHANNEL_FRAMEBUFFER 1
#define MAILBOX_CHANNEL_VIRTUAL_UART 2
#define MAILBOX_CHANNEL_VCHIQ 3
#define MAILBOX_CHANNEL_LEDS 4
#define MAILBOX_CHANNEL_BUTTONS 5
#define MAILBOX_CHANNEL_TOUCH_SCREEN 6
#define MAILBOX_CHANNEL_COUNT 7
#define MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC 8
#define MAILBOX_CHANNEL_PROPERTY_TAGS_VC_TO_ARM 9

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

#define MBOX_REQUEST 0
#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 1<<31
#define MBOX_EMPTY 1<<30

uint32_t mailbox_call(uint8_t channel);
uint32_t mailbox_read(uint8_t channel);
void mailbox_write(uint8_t channel, uint32_t data);
#endif //__BOARD_RASP_MAILBOX_H__
