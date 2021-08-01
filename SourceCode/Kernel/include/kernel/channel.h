//
// Created by XingfengYang on 2021/1/7.
//

#ifndef SYNESTIAOS_CHANNEL_H
#define SYNESTIAOS_CHANNEL_H

#include "libc/stdint.h"
#include "kernel/kqueue.h"

typedef struct MessageHeader {
    KQueueNode node;
    uint32_t id;
    uint32_t length;
    char *data;
} MessageHeader;

MessageHeader *message_create(struct MessageHeader *messageHeader, uint32_t id, uint32_t length, char *data);

typedef void (*ListenerOperationSend)(struct Listener *listener, MessageHeader *msgHdr);

typedef MessageHeader *(*ListenerOperationReceive)(struct Listener *listener, MessageHeader *msgHdr);

typedef void (*ListenerOperationFree)(struct Listener *listener);


typedef struct ListenerOperation {
    ListenerOperationSend send;
    ListenerOperationReceive receive;
    ListenerOperationFree free;
} ListenerOperation;

typedef struct Listener {
    struct Channel *channel;
    char name[NAME_LENGTH];
    ListenerOperation operation;
} Listener;

Listener *listener_create(struct Listener *listener, const char *name);

typedef void (*ChannelOperationUnRegister)(struct Channel *channel, struct Listener *listener);

typedef void (*ChannelOperationRegister)(struct Channel *channel, struct Listener *listener);

typedef void (*ChannelOperationSubscribe)(struct Channel *channel, struct Listener *listener);

typedef struct ChannelOperation {
    ChannelOperationRegister registe;
    ChannelOperationUnRegister unRegister;
    ChannelOperationSubscribe subscribe;
} ChannelOperation;

typedef struct Channel {
    char name[NAME_LENGTH];
    ChannelOperation operation;
    KernelQueue messageQueue;
} Channel;

Channel *channel_create(struct Channel *channel, const char *name);

#endif //SYNESTIAOS_CHANNEL_H
