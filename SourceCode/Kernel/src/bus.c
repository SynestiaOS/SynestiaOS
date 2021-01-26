//
// Created by XingfengYang on 2021/1/7.
//

#include "kernel/log.h"
#include "kernel/bus.h"
#include "libc/string.h"


MessageHeader *message_create(struct MessageHeader *messageHeader, uint32_t id, uint32_t length, char *data) {
    messageHeader->node.next = nullptr;
    messageHeader->node.prev = nullptr;
    messageHeader->data = data;
    messageHeader->length = length;
    messageHeader->id = id;

    return messageHeader;
}


void listener_operation_send(Listener *listener, MessageHeader *msgHdr) {
    if (listener->bus != nullptr) {
        listener->bus->messageQueue.operations.enqueue(&listener->bus->messageQueue, &msgHdr->node);
    } else {
        LogError("[ServiceBus] Listener %s not registered.\n", listener->name);
    }
}


void listener_operation_free(Listener *listener) {
    if (listener->bus != nullptr) {
        listener->bus->operation.unRegister(listener->bus, listener);
    }
    listener->bus = nullptr;
}

MessageHeader *listener_operation_receive(Listener *listener, MessageHeader *msgHdr) {
    if (!listener->bus->messageQueue.operations.isEmpty(&listener->bus->messageQueue)) {
        KQueueNode *node = listener->bus->messageQueue.operations.dequeue(&listener->bus->messageQueue);

        struct MessageHeader *messageHeader = getNode(node, struct MessageHeader, node);
        msgHdr = messageHeader;
        return msgHdr;
    } else {
        return nullptr;
    }
}


Listener *listener_create(Listener *listener, const char *name) {
    listener->operation.send = (ListenerOperationSend) listener_operation_send;
    listener->operation.receive = (ListenerOperationReceive) listener_operation_receive;
    listener->operation.free = (ListenerOperationFree) listener_operation_free;
    listener->bus = nullptr;
    memset(listener->name, 0, sizeof(listener->name));
    memcpy(listener->name, name, sizeof(listener->name) - 1);
    LogInfo("[ServiceBus] listener '%s' created.\n", name);
    return listener;
}


void service_bus_default_unregister(struct ServiceBus *bus, Listener *listener) {
    listener->bus = nullptr;
    LogInfo("[ServiceBus] listener '%s' unregistered from bus '%s'.\n", listener->name, bus->name);
}

void service_bus_default_register(struct ServiceBus *bus, Listener *listener) {
    listener->bus = bus;
    LogInfo("[ServiceBus] listener '%s' registered to bus '%s'.\n", listener->name, bus->name);
}

void service_bus_default_subscribe(struct ServiceBus *bus, Listener *listener) {
    // TODO
}

ServiceBus *service_bus_create(struct ServiceBus *serviceBus, const char *name) {
    serviceBus->operation.registe = (ServiceBusOperationRegister) service_bus_default_register;
    serviceBus->operation.unRegister = (ServiceBusOperationUnRegister) service_bus_default_unregister;
    serviceBus->operation.subscribe = (ServiceBusOperationSubscribe) service_bus_default_subscribe;
    memset(serviceBus->name, 0, sizeof(serviceBus->name));
    memcpy(serviceBus->name, name, sizeof(serviceBus->name) - 1);
    kqueue_create(&serviceBus->messageQueue);
    LogInfo("[ServiceBus] bus '%s' created.\n", name);
    return serviceBus;
}
