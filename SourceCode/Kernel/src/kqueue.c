//
// Created by XingfengYang on 2020/6/29.
//

#include <kqueue.h>


KernelStatus kqueue_enqueue(List *queue, List *node) {
    List *last;
    while (queue->next != nullptr) {
        last = queue->next;
    }
    last->next = node;
    node->prev = last;
    node->next = nullptr;
}

List *kqueue_dequeue(List *queue) {
    List *first;
    while (queue->prev != nullptr) {
        first = queue->prev;
    }
    first->next->prev = nullptr;
    first->next = nullptr;
    first->prev = nullptr;
    return first;
}
