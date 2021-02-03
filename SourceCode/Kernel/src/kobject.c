//
// Created by XingfengYang on 2020/12/3.
//

#include "kernel/kobject.h"
#include "kernel/mutex.h"
#include "kernel/semaphore.h"
#include "kernel/thread.h"

void *kernel_object_default_get(struct KernelObject *object) {
    switch (object->type) {
        case KERNEL_OBJECT_THREAD: {
            Thread *thread = getNode(object, Thread, object);
            return thread;
        }
        case KERNEL_OBJECT_MUTEX: {
            Mutex *mutex = getNode(object, Mutex, object);
            return mutex;
        }
        case KERNEL_OBJECT_SEMAPHORE: {
            Semaphore *semaphore = getNode(object, Semaphore, object);
            return semaphore;
        }
        case KERNEL_OBJECT_FILE_DESCRIPTOR: {
            FileDescriptor *fileDescriptor = getNode(object, FileDescriptor, object);
            return fileDescriptor;
        }
    }
}

uint32_t kernel_object_default_size(struct KernelObject *object) {
    switch (object->type) {
        case KERNEL_OBJECT_THREAD:
            return sizeof(Thread);
        case KERNEL_OBJECT_MUTEX:
            return sizeof(Mutex);
        case KERNEL_OBJECT_SEMAPHORE:
            return sizeof(Semaphore);
        case KERNEL_OBJECT_FILE_DESCRIPTOR:
            return sizeof(FileDescriptor);
        default:
            return 0;
    }
}

KernelObject *kobject_create(KernelObject *kObject, KernelObjectType type, KernelObjectStatus status) {
    kObject->operations.getObject = (KernelObjectOperationGetObject) kernel_object_default_get;
    kObject->operations.size = (KernelObjectOperationGetSize) kernel_object_default_size;
    kObject->list.next = nullptr;
    kObject->list.prev = nullptr;
    kObject->type = type;
    kObject->status = status;
}
