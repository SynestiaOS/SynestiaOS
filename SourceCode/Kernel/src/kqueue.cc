//
// Created by XingfengYang on 2020/6/29.
//

#include "kernel/kqueue.h"

KernelStatus kqueue_enqueue(KQueue *queue, KQueue *node) {
    klist_remove_node(node);

    KQueue *last = queue;
    if (last == nullptr) {
        queue = node;
        node->prev = nullptr;
        node->next = nullptr;
    }
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

uint32_t kqueue_size(KQueue *queue) { return klist_size(queue); }
