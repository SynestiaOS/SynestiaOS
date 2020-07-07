//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __BOARD_RASP3_MAILBOX_H__
#define __BOARD_RASP3_MAILBOX_H__

#include <stdint.h>
#include <raspi3.h>
/* a properly aligned buffer */
extern volatile uint32_t mailbox[36];

#define MBOX_REQUEST    0

/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

/* tags */
#define MBOX_TAG_SETPOWER       0x28001
#define MBOX_TAG_SETCLKRATE     0x38002
#define MBOX_TAG_SETVOLTAGE	0x38003
#define MBOX_TAG_LAST           0

#define MAIL_EMPTY	0x40000000		/* Mailbox Status Register: Mailbox Empty */
#define MAIL_FULL	0x80000000	/* Mailbox Status Register: Mailbox Full  */

int32_t mailbox_call(uint8_t ch);
bool mailbox_tag_write(uint32_t message);
uint32_t mailbox_tag_read();

#endif //__BOARD_RASP3_MAILBOX_H__
