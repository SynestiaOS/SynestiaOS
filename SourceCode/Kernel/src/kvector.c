//
// Created by XingfengYang on 2020/7/10.
//
#include <kvector.h>
#include <kheap.h>
#include <stdlib.h>


KernelVector *kvector_allocate() {
    // 1. allocate vector memory block from virtual memory (heap), and align.
    KernelVector *vector = (KernelVector *) kheap_alloc(DEFAULT_VECTOR_SIZE * sizeof(ListNode) + sizeof(KernelVector));
    if (vector == nullptr) {
        printf("[KVector] kVector allocate failed.\n");
        return nullptr;
    }
    vector->size = DEFAULT_VECTOR_SIZE;
    vector->index = 0;
    vector->node = (ListNode *) (vector + sizeof(KernelVector));
    return vector;
}

KernelStatus kvector_resize(KernelVector *vector, uint32_t newSize) {

}

KernelStatus kvector_free(KernelVector *vector) {

}

KernelStatus kvector_add(KernelVector *vector, ListNode *node) {

}

KernelStatus kvector_get(KernelVector *vector, uint32_t index) {

}

KernelStatus kvector_remove_index(KernelVector *vector, uint32_t index) {

}

KernelStatus kvector_remove(KernelVector *vector, ListNode *index) {

}

bool kvector_is_empty(KernelVector *vector) {

}

bool kvector_is_full(KernelVector *vector) {

}

KernelStatus kvector_clear(KernelVector *vector) {

}
