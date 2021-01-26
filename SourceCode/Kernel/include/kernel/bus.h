//
// Created by XingfengYang on 2021/1/7.
//

#ifndef SYNESTIAOS_BUS_H
#define SYNESTIAOS_BUS_H

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
    struct ServiceBus *bus;
    char name[NAME_LENGTH];
    ListenerOperation operation;
} Listener;

Listener *listener_create(struct Listener *listener, const char *name);


typedef void (*ServiceBusOperationUnRegister)(struct ServiceBus *bus, struct Listener *listener);

typedef void (*ServiceBusOperationRegister)(struct ServiceBus *bus, struct Listener *listener);

typedef void (*ServiceBusOperationSubscribe)(struct ServiceBus *bus, struct Listener *listener);

typedef struct BusOperation {
    ServiceBusOperationRegister registe;
    ServiceBusOperationUnRegister unRegister;
    ServiceBusOperationSubscribe subscribe;
} BusOperation;

typedef struct ServiceBus {
    char name[NAME_LENGTH];
    BusOperation operation;
    KernelQueue messageQueue;
} ServiceBus;

ServiceBus *service_bus_create(struct ServiceBus *serviceBus, const char *name);

#endif //SYNESTIAOS_BUS_H
