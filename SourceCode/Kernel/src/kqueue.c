//
// Created by XingfengYang on 2020/6/29.
//

#include <kqueue.h>


KernelStatus kqueue_enqueue(List *queue, List *node) {
    List *last = queue;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = node;
    node->prev = last;
    node->next = nullptr;
}

List *kqueue_dequeue(List *queue) {
    List *first = queue;
    while (first->prev != nullptr) {
        first = first->prev;
    }
    first->next->prev = nullptr;
    first->next = nullptr;
    first->prev = nullptr;
    return first;
}
