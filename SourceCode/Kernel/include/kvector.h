//
// Created by XingfengYang on 2020/7/10.
//

#ifndef __KERNEL_VECTOR_H__
#define __KERNEL_VECTOR_H__

#include <type.h>
#include "list.h"

#define DEFAULT_VECTOR_SIZE 12

typedef struct KernelVector {
    uint32_t size;
    ListNode **node;
    uint32_t index;
} __attribute__((packed)) KernelVector;

KernelVector *kvector_allocate();

KernelStatus kvector_resize(KernelVector *vector, uint32_t newSize);

KernelStatus kvector_free(KernelVector *vector);

KernelStatus kvector_add(KernelVector *vector, ListNode *node);

ListNode *kvector_get(KernelVector *vector, uint32_t index);

KernelStatus kvector_remove_index(KernelVector *vector, uint32_t index);

KernelStatus kvector_remove(KernelVector *vector, ListNode *index);

bool kvector_is_empty(KernelVector *vector);

bool kvector_is_full(KernelVector *vector);

KernelStatus kvector_clear(KernelVector *vector);

#endif //__KERNEL_VECTOR_H__
