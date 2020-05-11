OBJS =  src/io.o \
		src/interrupt.o \
		src/exception.ao \
		src/init.o


EXTRA_OBJS += arch/$(ARCH)/boot.ao \
			../Board/RaspberryPi3/src/uart.board.o \
			../Libraries/LibC/src/stdlib.library.o \
			../Board/RaspberryPi3/src/synestia_os_hal.board.o \

OBJ_SUFFIX = .kernel

PROGRAM = kernel

CFLAGS += -Iinclude
LDFLAGS += -T arch/$(ARCH)/kernel.ld

include ../Makefile.common
