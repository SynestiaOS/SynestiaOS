//
// Created by XingfengYang on 2020/7/10.
//

#ifndef __KERNEL_VECTOR_H__
#define __KERNEL_VECTOR_H__

#include "kernel/kobject.h"
#include "kernel/list.h"
#include "kernel/type.h"
#include "libc/stdbool.h"

#define DEFAULT_VECTOR_SIZE 12

typedef KernelStatus (*KernelVectorOperationResize)(struct KernelVector *vector, uint32_t newSize);

typedef KernelStatus (*KernelVectorOperationFree)(struct KernelVector *vector);

typedef KernelStatus (*KernelVectorOperationAdd)(struct KernelVector *vector, ListNode *node);

typedef ListNode *(*KernelVectorOperationGet)(struct KernelVector *vector, uint32_t index);

typedef uint32_t (*KernelVectorOperationSize)(struct KernelVector *vector);

typedef uint32_t (*KernelVectorOperationCapacity)(struct KernelVector *vector);

typedef bool (*KernelVectorOperationIsEmpty)(struct KernelVector *vector);

typedef bool (*KernelVectorOperationIsFull)(struct KernelVector *vector);

typedef KernelStatus (*KernelVectorOperationClear)(struct KernelVector *vector);

typedef struct KernelVectorOperations {
    KernelVectorOperationResize resize;
    KernelVectorOperationFree free;
    KernelVectorOperationAdd add;
    KernelVectorOperationGet get;
    KernelVectorOperationSize size;
    KernelVectorOperationCapacity capacity;
    KernelVectorOperationIsEmpty isEmpty;
    KernelVectorOperationIsFull isFull;
    KernelVectorOperationClear clear;
} KernelVectorOperations;

typedef struct KernelVector {
    uint32_t size;
    uint32_t capacity;
    KernelVectorOperations operations;
    ListNode **data;
} KernelVector;

KernelVector *kvector_allocate(struct KernelVector* vector);

#endif//__KERNEL_VECTOR_H__
