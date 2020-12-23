//
// Created by XingfengYang on 2020/6/29.
//

#include "kernel/kqueue.h"
#include "kernel/assert.h"

KernelStatus kqueue_default_operation_enqueue(struct KernelQueue *queue, KQueueNode *node) {
    if (queue->operations.isEmpty(queue)) {
        queue->head = node;
        queue->tail = node;
    } else {
        node->prev = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }
}

KQueueNode *kqueue_default_operation_dequeue(struct KernelQueue *queue) {
    DEBUG_ASSERT(queue->head != nullptr);
    if (!queue->operations.isEmpty(queue)) {

        KQueueNode *head = queue->head;
        queue->head = head->next;

        head->next->prev = nullptr;
        head->next = nullptr;
        head->prev = nullptr;
        return head;
    }
}

uint32_t kqueue_default_operation_size(struct KernelQueue *queue) {
    return queue->size;
}

bool kqueue_default_operation_is_empty(struct KernelQueue *queue) {
    return queue->size == 0;
}


KernelQueue *kqueue_create(KernelQueue *queue) {
    queue->size = 0;
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->operations.enqueue = kqueue_default_operation_enqueue;
    queue->operations.dequeue = kqueue_default_operation_dequeue;
    queue->operations.size = kqueue_default_operation_size;
    queue->operations.isEmpty = kqueue_default_operation_is_empty;
}
