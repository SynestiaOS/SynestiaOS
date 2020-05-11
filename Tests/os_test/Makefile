#OBJS =  cmocka/src/cmocka.o


EXTRA_OBJS += arch/$(ARCH)/os_test.ao \
			../../Kernel/src/io.kernel.o \
			../../Board/RaspberryPi3/src/uart.board.o
#			cmocka/src/cmocka.os_test.o

OBJ_SUFFIX = .os_test

OS_TEST_PROGRAM = os_test

CFLAGS += -Icmocka/include
CFLAGS += -I../../Kernel/arch/$(ARCH)/include
#CFLAGS += -I../../Libraries/LibC/include
LDFLAGS += -T ../../Kernel/arch/$(ARCH)/kernel.ld

OBJS =  os_test_main.o

include ../../Makefile.common
