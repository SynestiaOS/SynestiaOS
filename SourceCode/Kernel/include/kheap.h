//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_KHEAP_H__
#define __KERNEL_KHEAP_H__

#include <stdint.h>
#include <list.h>
#include "type.h"

typedef struct HeapArea {
    uint32_t size;
    ListNode list;
}  __attribute__((packed)) HeapArea;

extern uint32_t __heap_begin;

typedef void (*heap_alloc_func)(void *ptr, uint32_t size);

typedef void (*heap_free_func)(void *ptr);


KernelStatus kheap_init();

void kheap_set_alloc_callback(heap_alloc_func callback);

void kheap_set_free_callback(heap_free_func callback);

void *kheap_alloc(uint32_t size);

void *kheap_calloc(uint32_t num, uint32_t size);

void *kheap_realloc(void *ptr, uint32_t size);

KernelStatus kheap_free(void *ptr);

#endif //__KERNEL_KHEAP_H__
