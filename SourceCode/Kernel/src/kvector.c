//
// Created by XingfengYang on 2020/7/10.
//
#include "kernel/kernel.h"
#include "kernel/kvector.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "libc/stdlib.h"


extern DaVinciKernel kernel;

KernelStatus kvector_operation_default_resize(struct KernelVector *vector, uint32_t newSize) {
    vector->data = kernel.kernelHeap.operations.realloc(&kernel.kernelHeap, vector->data, newSize);
    if (vector == nullptr) {
        LogError("[KVector] kVector resize failed.\n");
        return ERROR;
    }
    return OK;
}

KernelStatus kvector_operation_default_free(struct KernelVector *vector) {
    KernelStatus status = kernel.kernelHeap.operations.free(&kernel.kernelHeap, vector);
    if (status != OK) {
        LogError("[KVector] kVector free failed.\n");
        return status;
    }
    return OK;
}

KernelStatus kvector_operation_default_add(struct KernelVector *vector, ListNode *node) {
    if (vector->size >= vector->capacity) {
        vector->capacity += DEFAULT_VECTOR_SIZE;
        KernelStatus status = vector->operations.resize(vector, vector->capacity * sizeof(ListNode *));
        if (status != OK) {
            LogError("[KVector] kVector resize failed.\n");
            return status;
        }
    }
    vector->data[vector->size] = node;
    vector->size++;
    return OK;
}

ListNode *kvector_operation_default_get(struct KernelVector *vector, uint32_t index) {
    if (index >= vector->size) {
        return nullptr;
    }
    return vector->data[index];
}

uint32_t kvector_operation_default_size(struct KernelVector *vector) {
    return vector->size;
}

uint32_t kvector_operation_default_capacity(struct KernelVector *vector) {
    return vector->capacity;
}

bool kvector_operation_default_isEmpty(struct KernelVector *vector) {
    return vector->size == 0;
}

bool kvector_operation_default_isFull(struct KernelVector *vector) {
    return vector->size == vector->capacity;
}

KernelStatus kvector_operation_default_clear(struct KernelVector *vector) {
    vector->size = 0;
    for (uint32_t i = 0; i < vector->size; i++) {
        vector->data = nullptr;
    }
    return OK;
}

KernelVector *kvector_allocate(struct KernelVector *vector) {
    // 1. allocate vector memory block from virtual memory (heap), and align.
    ListNode **data = (ListNode **) kernel.kernelHeap.operations.alloc(&kernel.kernelHeap, DEFAULT_VECTOR_SIZE * sizeof(ListNode *));
    if (data == nullptr) {
        LogError("[KVector] kVector allocate failed.\n");
        return nullptr;
    }
    vector->capacity = DEFAULT_VECTOR_SIZE;
    vector->size = 0;
    vector->data = (ListNode **) (data);

    vector->operations.resize = (KernelVectorOperationResize) kvector_operation_default_resize;
    vector->operations.free = (KernelVectorOperationFree) kvector_operation_default_free;
    vector->operations.add = (KernelVectorOperationAdd) kvector_operation_default_add;
    vector->operations.get = (KernelVectorOperationGet) kvector_operation_default_get;
    vector->operations.size = (KernelVectorOperationSize) kvector_operation_default_size;
    vector->operations.capacity = (KernelVectorOperationCapacity) kvector_operation_default_capacity;
    vector->operations.isEmpty = (KernelVectorOperationIsEmpty) kvector_operation_default_isEmpty;
    vector->operations.isFull = (KernelVectorOperationIsFull) kvector_operation_default_isFull;
    vector->operations.clear = (KernelVectorOperationClear) kvector_operation_default_clear;

    return vector;
}
