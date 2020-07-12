//
// Created by XingfengYang on 2020/7/6.
//

#ifndef __KERNEL_KVECTOR_TEST_H__
#define __KERNEL_KVECTOR_TEST_H__

#include <kvector.h>

void should_kvector_create() {
    KernelVector *kernelVector = kvector_allocate();
    ASSERT_NEQ(kernelVector, nullptr);
    ASSERT_EQ(kernelVector->index,0);
    ASSERT_EQ(kernelVector->size,DEFAULT_VECTOR_SIZE);
}


#endif //__KERNEL_KVECTOR_TEST_H__
