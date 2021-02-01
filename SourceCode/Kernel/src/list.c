//
// Created by XingfengYang on 2020/7/2.
//
#include "kernel/list.h"

KernelStatus klist_insert(ListNode *list, ListNode *node) {
    if (list->next != nullptr) {
        list->next->prev = node;
        node->next = list->next;
    }
    node->prev = list;
    list->next = node;
    return OK;
}

KernelStatus klist_append(ListNode *list, ListNode *node) {
    ListNode *tmp = list;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
    }
    node->prev = tmp;
    tmp->next = node;
    return OK;
}

ListNode *klist_get_head(ListNode *node) {
    ListNode *first = node;
    while (first->prev != nullptr) {
        first = first->prev;
    }
    return first;
}

ListNode *klist_remove_node(ListNode *node) {
    if (node->next == nullptr && node->prev == nullptr) {
        return node;
    }

    if (node->next == nullptr && node->prev != nullptr) {
        node->prev->next = nullptr;
        node->prev = nullptr;
        return node;
    }

    if (node->prev == nullptr && node->next != nullptr) {
        node->next->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    ListNode *prev = node->prev;
    ListNode *next = node->next;

    prev->next = next;
    next->prev = prev;

    node->next = nullptr;
    node->prev = nullptr;

    return node;
}

uint32_t klist_size(ListNode *node) {
    if (node == nullptr) {
        return 0;
    }
    ListNode *first = node;
    while (first->prev != nullptr) {
        first = first->prev;
    }

    uint32_t size = 1;
    while (first->next != nullptr) {
        first = first->next;
        size++;
    }

    return size;
}

void klist_iter(ListNode *list, void (*iterFunc)(ListNode *)) {
    struct ListNode *head = klist_get_head(list);
    if (head != nullptr) {
        iterFunc(head);
        if (head->next != nullptr) {
            head = head->next;
        }
    }
}
