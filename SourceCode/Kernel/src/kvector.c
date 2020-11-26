//
// Created by XingfengYang on 2020/7/10.
//
#include "kernel/kheap.h"
#include "kernel/kvector.h"
#include "kernel/log.h"
#include "libc/stdlib.h"

extern Heap kernelHeap;

KernelVector *kvector_allocate() {
    // 1. allocate vector memory block from virtual memory (heap), and align.
    KernelVector *vector = (KernelVector *) kernelHeap.operations.alloc(
            &kernelHeap, DEFAULT_VECTOR_SIZE * sizeof(ListNode *) + sizeof(KernelVector));
    if (vector == nullptr) {
        LogError("[KVector] kVector allocate failed.\n");
        return nullptr;
    }
    vector->size = DEFAULT_VECTOR_SIZE;
    vector->index = 0;
    vector->node = (ListNode **) (vector + sizeof(KernelVector));
    return vector;
}

KernelStatus kvector_resize(KernelVector *vector, uint32_t newSize) {
    vector = kernelHeap.operations.realloc(&kernelHeap, vector, newSize);
    if (vector == nullptr) {
        return ERROR;
    }
    vector->size = newSize;
    return OK;
}

KernelStatus kvector_free(KernelVector *vector) {
    KernelStatus status = kernelHeap.operations.free(&kernelHeap, vector);
    if (status != OK) {
        LogError("[KVector] kVector free failed.\n");
        return status;
    }
    return OK;
}

KernelStatus kvector_add(KernelVector *vector, ListNode *node) {
    if (vector->index >= vector->size) {
        vector->size += DEFAULT_VECTOR_SIZE;
        KernelStatus status = kvector_resize(vector, vector->size * sizeof(ListNode *) + sizeof(KernelVector));
        if (status != OK) {
            LogError("[KVector] kVector resiz failed.\n");
            return status;
        }
    }
    vector->node[vector->index] = node;
    vector->index++;
    return OK;
}

ListNode *kvector_get(KernelVector *vector, uint32_t index) { return vector->node[index]; }

KernelStatus kvector_remove_index(KernelVector *vector, uint32_t index) {}

KernelStatus kvector_remove(KernelVector *vector, ListNode *index) {}

uint32_t kvector_size(KernelVector *vector) { return vector->index; }

bool kvector_is_empty(KernelVector *vector) { return vector->index == 0; }

bool kvector_is_full(KernelVector *vector) { return vector->index == vector->size; }

KernelStatus kvector_clear(KernelVector *vector) {
    vector->index = 0;
    for (uint32_t i = 0; i < vector->size; i++) {
        vector->node = nullptr;
    }
    return OK;
}
