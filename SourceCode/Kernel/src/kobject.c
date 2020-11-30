#include "kernel/kobject.h"
#include "kernel/mutex.h"
#include "kernel/semaphore.h"
#include "kernel/Thread.h"

uint32_t KERNEL_OBJECT_SIZE[] = {
        sizeof(Thread), // THREAD
        sizeof(Mutex), // MUTEX
        sizeof(Semaphore), // SEMAPHORE
        sizeof(FileDescriptor) // FILE_DESCRIPTOR
};

uint32_t kobject_size(KernelObjectType type){
   return KERNEL_OBJECT_SIZE[type];
}
