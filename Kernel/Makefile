OBJS = \
	init.o

OBJ_SUFFIX = .kernel

EXTRA_OBJS = Arch/CortexA7/Boot/boot.ao

PROGRAM = kernel

LDFLAGS += -T linker.ld

all: $(PROGRAM)

include ../Makefile.common