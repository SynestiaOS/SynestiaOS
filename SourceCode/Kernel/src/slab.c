//
// Created by XingfengYang on 2020/11/23.
//
#include "kernel/slab.h"
#include "arm/page.h"
#include "kernel/kheap.h"
#include "kernel/kobject.h"
#include "kernel/log.h"
#include "kernel/mutex.h"
#include "kernel/semaphore.h"
#include "kernel/thread.h"
#include "kernel/type.h"

extern PhysicalPageAllocator kernelPageAllocator;
extern Heap kernelHeap;

void slab_default_alloc_callback(struct Slab *slab, KernelObjectType type, void *ptr, uint32_t reUse) {
    if (reUse) {
        slab->statistics.free[type]--;
    } else {
        slab->statistics.count[type]++;
    }
}

void slab_default_free_callback(struct Slab *slab, KernelObjectType type, void *ptr) {
    slab->statistics.free[type]++;
}

void *slab_default_alloc_kernel_object(struct Slab *slab, KernelObjectType type) {
    switch (type) {
        case KERNEL_OBJECT_THREAD: {
            Thread *thread = kernelHeap.operations.alloc(&kernelHeap, sizeof(Thread));
            if (slab->kernelObjects[type] == nullptr) {
                slab->kernelObjects[type] = &thread->object.list;
            } else {
                klist_append(slab->kernelObjects[type], &thread->object.list);
            }
            thread->object.status = USING;
            return thread;
        }
        case KERNEL_OBJECT_MUTEX: {
            Mutex *mutex = kernelHeap.operations.alloc(&kernelHeap, sizeof(Mutex));
            if (slab->kernelObjects[type] == nullptr) {
                slab->kernelObjects[type] = &mutex->object.list;
            } else {
                klist_append(slab->kernelObjects[type], &mutex->object.list);
            }
            mutex->object.status = USING;
            return mutex;
        }
        case KERNEL_OBJECT_SEMAPHORE: {
            Semaphore *semaphore = kernelHeap.operations.alloc(&kernelHeap, sizeof(Semaphore));
            if (slab->kernelObjects[type] == nullptr) {
                slab->kernelObjects[type] = &semaphore->object.list;
            } else {
                klist_append(slab->kernelObjects[type], &semaphore->object.list);
            }
            semaphore->object.status = USING;
            return semaphore;
        }
        case KERNEL_OBJECT_FILE_DESCRIPTOR: {
            FileDescriptor *fileDescriptor = kernelHeap.operations.alloc(&kernelHeap, sizeof(FileDescriptor));
            if (slab->kernelObjects[type] == nullptr) {
                slab->kernelObjects[type] = &fileDescriptor->object.list;
            } else {
                klist_append(slab->kernelObjects[type], &fileDescriptor->object.list);
            }
            fileDescriptor->object.status = USING;
            return fileDescriptor;
        }
    }
}

void *slab_default_alloc(struct Slab *slab, KernelObjectType type) {
    // can not found any kernel object from kernel object lists
    if (slab->kernelObjects[type] == nullptr) {
        // alloc a new kernel object from heap and link it to kernel object list
        void *ptr = slab_default_alloc_kernel_object(slab, type);
        slab->allocCallback(slab, type, ptr, 0);
        return ptr;
    } else {
        KernelObject *kernelObject = getNode(slab->kernelObjects[type], KernelObject, list);

        // the first of kernel object list is free
        if (kernelObject->status == FREE) {
            // just use it, and mark it as used
            kernelObject->status = USING;
            void *ptr = kernelObject->operations.getObject(&kernelObject);
            slab->allocCallback(slab, type, ptr, 1);
            return ptr;
        } else {
            // let find the free kernel object from list
            while (kernelObject->list.next != nullptr) {
                if (getNode(kernelObject->list.next, KernelObject, list)->status == FREE) {
                    kernelObject->status = USING;
                    return kernelObject->operations.getObject(&kernelObject);
                }
                kernelObject = (KernelObject *) kernelObject->list.next;
            }
            // oops, not found free kernel object, so let's alloc from heap.
            void *ptr = slab_default_alloc_kernel_object(slab, type);
            slab->allocCallback(slab, type, ptr, 0);
            return ptr;
        }
    }
}

KernelStatus slab_default_free(struct Slab *slab, KernelObjectType type, void *ptr) {
    // set kernel object free, then remove from kernel object list, at last insert the removed node to head of list.
    switch (type) {
        case KERNEL_OBJECT_THREAD: {
            Thread *thread = (Thread *) ptr;
            if (klist_size(slab->kernelObjects[type]) > 1) {
                klist_remove_node(&thread->object.list);
                thread->object.list.next = slab->kernelObjects[type];
            } else {
                klist_remove_node(&thread->object.list);
            }
            slab->kernelObjects[type] = &thread->object.list;
            thread->object.status = FREE;
            slab->freeCallback(slab, KERNEL_OBJECT_THREAD, thread);
            return OK;
        }
        case KERNEL_OBJECT_MUTEX: {
            Mutex *mutex = (Mutex *) ptr;
            if (klist_size(slab->kernelObjects[type]) != 1) {
                klist_remove_node(&mutex->object.list);
                mutex->object.list.next = slab->kernelObjects[type];
            } else {
                klist_remove_node(&mutex->object.list);
            }
            slab->kernelObjects[type] = &mutex->object.list;
            mutex->object.status = USING;
            slab->freeCallback(slab, KERNEL_OBJECT_MUTEX, mutex);
            return OK;
        }
        case KERNEL_OBJECT_SEMAPHORE: {
            Semaphore *semaphore = (Semaphore *) ptr;
            if (klist_size(slab->kernelObjects[type]) != 1) {
                klist_remove_node(&semaphore->object.list);
                semaphore->object.list.next = slab->kernelObjects[type];
            } else {
                klist_remove_node(&semaphore->object.list);
            }
            slab->kernelObjects[type] = &semaphore->object.list;
            semaphore->object.status = USING;
            slab->freeCallback(slab, KERNEL_OBJECT_SEMAPHORE, semaphore);
            return OK;
        }
        case KERNEL_OBJECT_FILE_DESCRIPTOR: {
            FileDescriptor *fileDescriptor = (FileDescriptor *) ptr;
            if (klist_size(slab->kernelObjects[type]) != 1) {
                klist_remove_node(&fileDescriptor->object.list);
                fileDescriptor->object.list.next = slab->kernelObjects[type];
            } else {
                klist_remove_node(&fileDescriptor->object.list);
            }
            slab->kernelObjects[type] = &fileDescriptor->object.list;
            fileDescriptor->object.status = USING;
            slab->freeCallback(slab, KERNEL_OBJECT_FILE_DESCRIPTOR, fileDescriptor);
            return OK;
        }
    }
}

void slab_default_set_alloc_callback(struct Slab *slab, SlabAllocCallback callback) {
    slab->allocCallback = callback;
}

void slab_default_set_free_callback(struct Slab *slab, SlabFreeCallback callback) {
    slab->freeCallback = callback;
}

KernelStatus slab_create(Slab *slab, uint32_t addr, uint32_t size) {
    slab->allocCallback = (SlabAllocCallback) slab_default_alloc_callback;
    slab->freeCallback = (SlabFreeCallback) slab_default_free_callback;

    slab->address = addr;
    LogInfo("[KSlab] at: %d. \n", slab->address);

    PhysicalPageAllocator *physicalPageAllocator = &kernelPageAllocator;

    // allocate physical page for slab
    uint32_t slabPhysicalPage = (uint32_t) physicalPageAllocator->operations.allocHugeAt(
            physicalPageAllocator, USAGE_KERNEL_HEAP, (slab->address | 4 * KB) >> VA_OFFSET, size - slab->address);
    LogInfo("[KSlab] alloc slab page: %d. \n", (uint32_t) slabPhysicalPage);

    slab->address = KERNEL_PHYSICAL_START + slabPhysicalPage * PAGE_SIZE;
    LogInfo("[KSlab] kheap at: %d. \n", slab->address);

    slab->operations.setFreeCallback = (SlabOperationSetFreeCallback) slab_default_set_free_callback;
    slab->operations.setAllocCallback = (SlabOperationSetAllocCallback) slab_default_set_alloc_callback;

    slab->operations.alloc = (SlabOperationAlloc) slab_default_alloc;
    slab->operations.free = (SlabOperationFree) slab_default_free;

    LogInfo("[KSlab] kernel slab created. \n");
    return OK;
}
