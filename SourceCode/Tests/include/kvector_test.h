//
// Created by XingfengYang on 2020/7/6.
//

#ifndef __KERNEL_KVECTOR_TEST_H__
#define __KERNEL_KVECTOR_TEST_H__

#include <kvector.h>

void should_kvector_create() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);
}

void should_kvector_resize() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    kvector_resize(kernelVector, DEFAULT_VECTOR_SIZE * 2);
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE * 2);

}

void should_kvector_free() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    kvector_free(kernelVector);
    ASSERT_EQ(kernelVector, nullptr);
}

void should_kvector_add() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ListNode node;
    kvector_add(kernelVector, &node);
    kvector_add(kernelVector, &node);
    ASSERT_EQ(kernelVector->index, 2);
}

void should_kvector_get() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ListNode node;
    kvector_add(kernelVector, &node);
    kvector_add(kernelVector, &node);
    ASSERT_EQ(kernelVector->index, 2);

    ListNode n = kvector_get(kernelVector, 1);
    ASSERT_EQ(&node, &n);

}

void should_kvector_remove_index() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ListNode node;
    kvector_add(kernelVector, &node);
    kvector_add(kernelVector, &node);
    ASSERT_EQ(kernelVector->index, 2);

    kvector_remove_index(kernelVector, 0);
    ASSERT_EQ(kernelVector->index, 1);
}

void should_kvector_remove() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ListNode node;
    kvector_add(kernelVector, &node);
    kvector_add(kernelVector, &node);
    ASSERT_EQ(kernelVector->index, 2);

    kvector_remove(kernelVector, &node);
    ASSERT_EQ(kernelVector->index, 1);
}

void should_kvector_is_empty() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ASSERT_TRUE(kvector_is_empty(kernelVector));
}

void should_kvector_is_full() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ListNode node;
    for (uint32_t i = 0; i < DEFAULT_VECTOR_SIZE; i++) {
        kvector_add(kernelVector, &node);
    }
    ASSERT_TRUE(kvector_is_full(kernelVector));
}

void should_kvector_clear() {

    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index, 0);
    ASSERT_EQ(kernelVector->size, DEFAULT_VECTOR_SIZE);

    ListNode node;
    for (uint32_t i = 0; i < DEFAULT_VECTOR_SIZE; i++) {
        kvector_add(kernelVector, &node);
    }

    kvector_clear(kernelVector);
    ASSERT_TRUE(kvector_is_empty(kernelVector));
    ASSERT_EQ(kernelVector->index, 0);
}

#endif //__KERNEL_KVECTOR_TEST_H__
