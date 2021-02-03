#include <kernel/slab.h>
#include <kernel/log.h>

extern Slab kernelObjectSlab;

void dump_slab_statistics(const char *info)
{
    if (info != nullptr)  LogInfo("%s\n", info)
    LogInfo("********** Slab Statistics **********\n", info)
    LogInfo("addr: 0x%x.\n", kernelObjectSlab.address)
    LogInfo("maxSizeLimit: 0x%x.\n", kernelObjectSlab.maxSizeLimit)
    LogInfo("count:\n")
    for (uint32_t i = 0; i < KERNEL_OBJECT_TYPE_BUTT; i++) {
        LogInfo("0x%08x ", kernelObjectSlab.statistics.count[i])
    }
    LogInfo("\nfree:\n")
    for (uint32_t i = 0; i < KERNEL_OBJECT_TYPE_BUTT; i++) {
        LogInfo("0x%08x ", kernelObjectSlab.statistics.free[i])
    }
    char *type[] = {"THREAD", "MUTEX", "SEM", "FILE_DESCR"};
    uint32_t type_count = sizeof(type) / sizeof(char *);

    for (uint32_t i = 0; i < KERNEL_OBJECT_TYPE_BUTT; i++) {
        ListNode *node = kernelObjectSlab.kernelObjects[i];
        if (node != nullptr)
            LogInfo("\nnode        type  status    next    pre\n")
        while (node != nullptr) {
            KernelObject *object = getNode(node, KernelObject, list);
            LogInfo("0x%x  %s  %s  0x%x  0x%x\n", node,
                    (object->type < type_count) ? type[object->type] : "unknown",
                    (object->status == USING) ? "Using": "Free", node->next, node->prev)
            node = node->next;
        }
    }
}


void test_slab1()
{
    dump_slab_statistics("---before alloc---");
    void *ptr1 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_THREAD);
    dump_slab_statistics("---after alloc---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_THREAD, ptr1);
    dump_slab_statistics("---after free1---");

    void *ptr2 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_THREAD);
    dump_slab_statistics("---after alloc2---");

    void *ptr3 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_THREAD);
    dump_slab_statistics("---after alloc3---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_THREAD, ptr3);
    dump_slab_statistics("---after free3---");
    void *ptr4 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_THREAD);
    dump_slab_statistics("---after alloc4---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_THREAD, ptr2);
    dump_slab_statistics("---after free2---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_THREAD, ptr4);
    dump_slab_statistics("---after free4---");

}

void test_slab()
{
    dump_slab_statistics("---before alloc---");
    void *ptr1 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_MUTEX);
    dump_slab_statistics("---after alloc1---");

    void *ptr2 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_FILE_DESCRIPTOR);
    dump_slab_statistics("---after alloc2---");

    void *ptr3 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_MUTEX);
    dump_slab_statistics("---after alloc3---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_MUTEX, ptr3);
    dump_slab_statistics("---after free3---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_FILE_DESCRIPTOR, ptr2);
    dump_slab_statistics("---after free2---");

    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_MUTEX, ptr1);
    dump_slab_statistics("---after free1---");

    void *ptr4 = kernelObjectSlab.operations.alloc(&kernelObjectSlab, KERNEL_OBJECT_FILE_DESCRIPTOR);
    dump_slab_statistics("---after alloc4---");
    kernelObjectSlab.operations.free(&kernelObjectSlab, KERNEL_OBJECT_FILE_DESCRIPTOR, ptr4);
    dump_slab_statistics("---after free4---");
}