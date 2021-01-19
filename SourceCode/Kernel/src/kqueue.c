//
// Created by XingfengYang on 2020/6/29.
//

#include "kernel/kqueue.h"
#include "kernel/assert.h"

KernelStatus kqueue_default_operation_enqueue(struct KernelQueue *queue, KQueueNode *node) {
    if (queue->operations.isEmpty(queue)) {
        queue->head = node;
        queue->tail = node;
    } else if (queue->size == 1) {
        if (node == queue->head) {
            return OK;
        }
    } else {
        node->prev = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
    return OK;
}

KQueueNode *kqueue_default_operation_dequeue(struct KernelQueue *queue) {
    if (!queue->operations.isEmpty(queue)) {

        KQueueNode *head = queue->head;
        queue->head = head->next;

        queue->size--;

        head->next->prev = nullptr;
        head->next = nullptr;
        head->prev = nullptr;
        return head;
    }
    return nullptr;
}

uint32_t kqueue_default_operation_size(struct KernelQueue *queue) {
    return queue->size;
}

bool kqueue_default_operation_is_empty(struct KernelQueue *queue) {
    return queue->size == 0 && queue->head == queue->tail;
}


KernelQueue *kqueue_create(KernelQueue *queue) {
    queue->size = 0;
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->operations.enqueue = (KernelQueueOperationEnQueue) kqueue_default_operation_enqueue;
    queue->operations.dequeue = (KernelQueueOperationDeQueue) kqueue_default_operation_dequeue;
    queue->operations.size = (KernelQueueOperationSize) kqueue_default_operation_size;
    queue->operations.isEmpty = (KernelQueueOperationIsEmpty) kqueue_default_operation_is_empty;
    return queue;
}
