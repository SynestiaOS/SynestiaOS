//
// Created by XingfengYang on 2021/1/7.
//

#include "kernel/log.h"
#include "kernel/channel.h"
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
    if (listener->channel != nullptr) {
        listener->channel->messageQueue.operations.enqueue(&listener->channel->messageQueue, &msgHdr->node);
    } else {
        LogError("[Channel] Listener %s not registered.\n", listener->name);
    }
}

void listener_operation_free(Listener *listener) {
    if (listener->channel != nullptr) {
        listener->channel->operation.unRegister(listener->channel, listener);
    }
    listener->channel = nullptr;
}

MessageHeader *listener_operation_receive(Listener *listener, MessageHeader *msgHdr) {
    if (!listener->channel->messageQueue.operations.isEmpty(&listener->channel->messageQueue)) {
        KQueueNode *node = listener->channel->messageQueue.operations.dequeue(&listener->channel->messageQueue);

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
    listener->channel = nullptr;
    memset(listener->name, 0, sizeof(listener->name));
    memcpy(listener->name, name, sizeof(listener->name) - 1);
    LogInfo("[Channel] listener '%s' created.\n", name);
    return listener;
}

void channel_default_unregister(struct Channel *channel, Listener *listener) {
    listener->channel = nullptr;
    LogInfo("[Channel] listener '%s' unregistered from channel '%s'.\n", listener->name, channel->name);
}

void channel_default_register(struct Channel *channel, Listener *listener) {
    listener->channel = channel;
    LogInfo("[Channel] listener '%s' registered to channel '%s'.\n", listener->name, channel->name);
}

void channel_default_subscribe(struct Channel *channel, Listener *listener) {
    // TODO
}

Channel *channel_create(struct Channel *channel, const char *name) {
    channel->operation.registe = (ChannelOperationRegister) channel_default_register;
    channel->operation.unRegister = (ChannelOperationUnRegister) channel_default_unregister;
    channel->operation.subscribe = (ChannelOperationSubscribe) channel_default_subscribe;
    memset(channel->name, 0, sizeof(channel->name));
    memcpy(channel->name, name, sizeof(channel->name) - 1);
    kqueue_create(&channel->messageQueue);
    LogInfo("[Channel] bus '%s' created.\n", name);
    return channel;
}
