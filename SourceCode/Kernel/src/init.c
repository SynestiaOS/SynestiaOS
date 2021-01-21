#include "arm/register.h"
#include "arm/kernel_vmm.h"
#include "arm/page.h"
#include "kernel/vfs.h"
#include "libgui/gui_window.h"
#include "raspi2/synestia_os_hal.h"
#include "libgfx/gfx2d.h"
#include "raspi2/led.h"
#include "libelf/elf.h"
#include "kernel/kernel.h"

DaVinciKernel kernel;

extern void test_threads_init(void);

void kernel_main(void) {
    if (read_cpuid() == 0) {
        led_init();
        synestia_init_bsp();
        // init kernel virtual memory mapping
        kernel_vmm_init();

        daVinci_create(&kernel);
        kernel.operation.init(&kernel);

        Elf elf;
        uint32_t *data = (uint32_t *) kernel.kernelHeap.operations.alloc(&kernel.kernelHeap, 40 * KB);
        vfs_kernel_read(&kernel.vfs, "/initrd/bin/TestApp.elf", data, 40 * KB);
        elf_init(&elf, data);
        elf.operations.dump(&elf);

        test_threads_init();

        kernel.operation.start(&kernel);
    }

    // schd_switch_next();
}
