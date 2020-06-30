//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_LIST_H__
#define __KERNEL_LIST_H__

#define getNode(ptr, type, member)((type *)((char *)(ptr) - (char *)(&(((type *)0)->member))))

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
}  __attribute__((packed)) ListNode;

#endif //__KERNEL_LIST_H__
