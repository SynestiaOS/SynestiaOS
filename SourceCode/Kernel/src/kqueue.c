//
// Created by XingfengYang on 2020/6/29.
//

#include <kqueue.h>


KernelStatus kqueue_enqueue(KQueue *queue, KQueue *node) {
    KQueue *last = queue;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = node;
    node->prev = last;
    node->next = nullptr;

    return OK;
}

KQueue *kqueue_dequeue(KQueue *queue) {
    KQueue *first = queue;
    while (first->prev != nullptr) {
        first = first->prev;
    }
    first->next->prev = nullptr;
    first->next = nullptr;
    first->prev = nullptr;
    return first;
}

uint32_t kqueue_size(KQueue *queue) {
    KQueue *first = queue;
    while (first->prev != nullptr) {
        first = first->prev;
    }

    uint32_t size = 0;
    while (first->next != nullptr) {
        first = first->next;
        size++;
    }

    return size;
}
