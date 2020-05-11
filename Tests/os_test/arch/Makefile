OBJS =

EXTRA_OBJS += arch/$(ARCH)/os_test.ao

OBJ_SUFFIX = .kernel

PROGRAM = kernel

CFLAGS += -Iinclude
LDFLAGS += -T ../../../Kernel/arch/$(ARCH)/kernel.ld

include ../Makefile.common
