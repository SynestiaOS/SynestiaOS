//
// Created by XingfengYang on 2020/7/7.
//

#include <mailbox.h>
#include <stdbool.h>
#include <stdlib.h>

MailMessage mailbox_call(MailMessage message) {
  while (!((*(uint32_t *)(MAIL0_STATUS)) & MBOX_EMPTY)) {
    *(uint32_t *)(MAIL0_READ);
  }
  mailbox_send(message);
  MailMessage data = mailbox_read(message.channel);
  return data;
}

MailMessage mailbox_read(uint8_t channel) {
  MailStatus stat;
  MailMessage res;
  do {
    do {
      stat.empty = *MAIL0_STATUS & MBOX_EMPTY;
      stat.full = *MAIL0_STATUS & MBOX_FULL;
    } while (stat.empty);
    res.channel = *MAIL0_READ & 0xF;
    res.data = *MAIL0_READ & ~0xF;
  } while (res.channel != channel);
  return res;
}

void mailbox_send(MailMessage msg) {
  MailStatus stat;
  do {
    stat.empty = *MAIL0_STATUS & MBOX_EMPTY;
    stat.full = *MAIL0_STATUS & MBOX_FULL;
  } while (stat.full);

  *MAIL0_WRITE = (msg.data | msg.channel);
}
