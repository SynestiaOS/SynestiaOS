//
// Created by XingfengYang on 2020/7/7.
//

#include "raspi2/mailbox.h"
#include "libc/stdlib.h"

MailMessage mailbox_call(MailMessage message) {
    mailbox_send(message);
    MailMessage data = mailbox_read(message);
    return data;
}

MailMessage mailbox_read(MailMessage msg) {
    MailStatus stat;
    MailMessage res;
    do {
        do {
            stat.empty = *MAIL0_STATUS & MBOX_EMPTY;
        } while (stat.empty);
        if((msg.data | msg.channel) == *MAIL0_READ)
            return msg;
    } while (1);
    return res;
}

void mailbox_send(MailMessage msg) {
    MailStatus stat;
    do {
        //stat.empty = *MAIL1_STATUS & MBOX_EMPTY;
        stat.full = *MAIL1_STATUS & MBOX_FULL;
    } while (stat.full);

    *MAIL1_WRITE = (msg.data | msg.channel);
}
