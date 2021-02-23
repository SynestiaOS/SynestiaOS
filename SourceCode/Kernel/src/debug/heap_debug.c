#include <arm/page.h>
#include <kernel/log.h>
#include <kernel/kheap.h>
#include <debug/heap_debug.h>

extern PhysicalPageAllocator kernelPageAllocator;
extern PhysicalPageAllocator userspacePageAllocator;
extern Heap kernelHeap;

static void dump_physical_page_alloc_status()
{
    LogInfo("********** Physical Page Alloc Status **********\n")
    LogInfo("base: 0x%x\n", userspacePageAllocator.base)
    LogInfo("size: 0x%x\n", userspacePageAllocator.size)
    return;
}

static void dump_user_space_page_alloc_status()
{
    LogInfo("********** User Space Page Alloc Status **********\n")
    LogInfo("base: 0x%x\n", userspacePageAllocator.base)
    LogInfo("size: 0x%x\n", userspacePageAllocator.size)
    return;
}

static void dump_heap_statistics()
{
    LogInfo("********** Heap Statistics **********\n")
    LogInfo("heap begin at address: 0x%x\n", kernelHeap.address)
    LogInfo("max size: 0x%x\n", kernelHeap.maxSizeLimit)
    LogInfo("allocatedBlockCount: 0x%x\n", kernelHeap.statistics.allocatedBlockCount)
    LogInfo("allocatedSize: 0x%x\n", kernelHeap.statistics.allocatedSize)
    LogInfo("mergeCounts: 0x%x\n", kernelHeap.statistics.mergeCounts)
    return;
}

static void dump_heap_using_list()
{
    HeapArea *using_ptr = kernelHeap.usingListHead;
    LogInfo("********** Heap Using List **********\n")
    LogInfo("using_ptr = 0x%x\n", using_ptr)
//    for(uint32_t i = 0; i < 64; i++) {
//        LogInfo("0x%x : 0x%x\n", (u32)using_ptr + i * 4, *(u32*)((u32)using_ptr + i * 4))
//    }
    if (using_ptr) {
        uint32_t count = 0;
        ListNode node = using_ptr->list;
        HeapArea *area_ptr = (HeapArea *)using_ptr;
        LogInfo("heap 0x%x: next : 0x%x  pre : 0x%x, size = 0x%x\n",
                count++, area_ptr->list.next, area_ptr->list.prev, area_ptr->size);
        for (; node.next != nullptr; node = *(node.next) , count++) {
            /* according to the structure of HeapArea, node->next should make a u32 of magic + u32 of size */
            HeapArea *info = (HeapArea *)((uint32_t)node.next - 2 * sizeof(uint32_t));
            LogInfo("heap 0x%x: next : 0x%x  pre : 0x%x, size = 0x%x\n",
                    count, info->list.next, info->list.prev, info->size);
        }
    }
    return;
}

static void dump_heap_free_list()
{
    HeapArea *free_ptr = kernelHeap.freeListHead;
    LogInfo("********** Heap Free List **********\n")
    LogInfo("free_ptr = 0x%x\n", free_ptr)
//    for(uint32_t i = 0; i < 64; i++) {
//        LogInfo("0x%x : 0x%x\n", (u32)free_ptr + i * 4, *(u32*)((u32)free_ptr + i * 4))
//    }
    if (free_ptr) {
        uint32_t count = 0;
        ListNode node = free_ptr->list;
        HeapArea *area_ptr = (HeapArea *)free_ptr;
        LogInfo("heap 0x%x: next : 0x%x  pre : 0x%x, size = 0x%x\n",
                count++, area_ptr->list.next, area_ptr->list.prev, area_ptr->size);
        for (; node.next != nullptr; node = *(node.next) , count++) {
            /* according to the structure of HeapArea, node->next should make a u32 of magic + u32 of size */
            HeapArea *info = (HeapArea *)((uint32_t)node.next - 2 * sizeof(uint32_t));
            LogInfo("heap 0x%x: next : 0x%x  pre : 0x%x, size = 0x%x\n",
                    count, info->list.next, info->list.prev, info->size);
        }
    }
    return;
}

void dump_kernel_heap(uint32_t type, const char* extend_info)
{
    if (extend_info) LogInfo("********** %s **********\n", extend_info);

    if ((type & GET_HEAP_STAT) != 0) {
        dump_heap_statistics();
    }
    if ((type & GET_USING_LIST) != 0) {
        dump_heap_using_list();
    }
    if ((type & GET_FREE_LIST) != 0) {
        dump_heap_free_list();
    }
    if ((type & GET_PHYSICAL_PAGE) != 0) {
        dump_physical_page_alloc_status();
    }
    if ((type & GET_USER_SPACE_PAGE) != 0) {
        dump_user_space_page_alloc_status();
    }
}

void heap_test()
{
    dump_kernel_heap(GET_HEAP_STAT, "before");
    void *ptr1 = kernelHeap.operations.alloc(&kernelHeap, sizeof(uint32_t));
    dump_kernel_heap(GET_HEAP_STAT, "after alloc 4");
    void *ptr2 = kernelHeap.operations.alloc(&kernelHeap, 2 * sizeof(uint32_t));
    dump_kernel_heap(GET_HEAP_STAT,"after alloc 4 + 8");
    void *ptr3 = kernelHeap.operations.alloc(&kernelHeap, 3 * sizeof(uint32_t));
    dump_kernel_heap(GET_HEAP_STAT, "after alloc 4 + 8 + 12");

    kernelHeap.operations.free(&kernelHeap, ptr1);
    dump_kernel_heap(GET_HEAP_STAT|GET_USING_LIST|GET_FREE_LIST|GET_PHYSICAL_PAGE|GET_USER_SPACE_PAGE,"after free 4");
    kernelHeap.operations.free(&kernelHeap, ptr2);
    dump_kernel_heap(GET_HEAP_STAT,"after free 4 + 8");
    kernelHeap.operations.free(&kernelHeap, ptr3);
    dump_kernel_heap(GET_HEAP_STAT, "after free 4 + 8 + 12");
    void *ptr4 = kernelHeap.operations.alloc(&kernelHeap, sizeof(uint32_t));
    dump_kernel_heap(GET_HEAP_STAT, "after alloc new 4");
    kernelHeap.operations.free(&kernelHeap, ptr4);
    dump_kernel_heap(GET_HEAP_STAT|GET_USING_LIST|GET_FREE_LIST|GET_PHYSICAL_PAGE|GET_USER_SPACE_PAGE, "after free new 4");
}