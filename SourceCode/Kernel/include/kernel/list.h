//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_LIST_H__
#define __KERNEL_LIST_H__

#include "kernel/type.h"
#include "libc/stdint.h"

#define offsetOf(type, member) (char *) (&(((type *) 0)->member))
#define getNode(ptr, type, member) ((type *) ((char *) (ptr) - (char *) (&(((type *) 0)->member))))

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

KernelStatus klist_insert(ListNode *list, ListNode *node);

KernelStatus klist_append(ListNode *list, ListNode *node);

ListNode *klist_remove_node(ListNode *node);

ListNode *klist_get_head(ListNode *node);

uint32_t klist_size(ListNode *node);

void klist_iter(ListNode *list, void (*iterFunc)(ListNode *));

#endif//__KERNEL_LIST_H__
