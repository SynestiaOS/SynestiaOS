OBJS =  src/main.o \
		src/uart.o


EXTRA_OBJS = arch/$(ARCH)/boot.ao

OBJ_SUFFIX = .kernel

PROGRAM = kernel

CFLAGS += -Iinclude -D$(PLATFORM)
LDFLAGS += -T arch/$(ARCH)/kernel.ld

all: $(PROGRAM)

include ../Makefile.common