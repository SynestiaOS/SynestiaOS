#define MEGABYTE		0x100000	// do not change

// KERNEL_MAX_SIZE is the maximum allowed size of a built kernel image.
// If your kernel image contains big data areas it may be required to
// increase this value. The value must be a multiple of 16 KByte.

#ifndef KERNEL_MAX_SIZE
#define KERNEL_MAX_SIZE		(10 * MEGABYTE)
#endif
#define PAGE_SIZE		4096				// page size used by us

#define KERNEL_STACK_SIZE	0x20000				// all sizes must be a multiple of 16K
#define EXCEPTION_STACK_SIZE	0x8000
#define PAGE_TABLE1_SIZE	0x4000
#define PAGE_RESERVE		(4 * MEGABYTE)

#define MEM_KERNEL_START	0x8000
#define MEM_KERNEL_END		(MEM_KERNEL_START + KERNEL_MAX_SIZE)
#define MEM_KERNEL_STACK	(MEM_KERNEL_END + KERNEL_STACK_SIZE)		// expands down

#define CORES			4					// must be a power of 2
#define MEM_ABORT_STACK		(MEM_KERNEL_STACK + KERNEL_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
#define MEM_IRQ_STACK		(MEM_ABORT_STACK + EXCEPTION_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
#define MEM_FIQ_STACK		(MEM_IRQ_STACK + EXCEPTION_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
#define MEM_PAGE_TABLE1		(MEM_FIQ_STACK + EXCEPTION_STACK_SIZE * (CORES-1))
