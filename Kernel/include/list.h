//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_LIST_H__
#define __KERNEL_LIST_H__

#define getNode(ptr, type, member)((type *)((char *)(ptr) - (char *)(&(((type *)0)->member))))

typedef struct List{
    struct List *prev;
    struct List *next;
} List __attribute__((packed));

#endif //__KERNEL_LIST_H__
