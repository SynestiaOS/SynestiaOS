#include "libc/macros.h"
#include "arm/cpu.h"
#include "arm/kernel_vmm.h"
#include "arm/mmu.h"
#include "arm/page.h"
#include "kernel/ext2.h"
#include "kernel/interrupt.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "kernel/sched.h"
#include "kernel/spinlock.h"
#include "kernel/vfs.h"
#include "libc/stdlib.h"
#include "libc/string.h"
#include "libelf/elf.h"
#include "libgfx/font8bits.h"
#include "libgfx/gfx2d.h"
#include "libgui/gui_animation.h"
#include "libgui/gui_button.h"
#include "libgui/gui_canvas.h"
#include "libgui/gui_label.h"
#include "libgui/gui_panel.h"
#include "libgui/gui_view3d.h"
#include "libgui/gui_window.h"
#include "raspi2/gpu.h"
#include "raspi2/synestia_os_hal.h"

extern uint32_t __HEAP_BEGIN;
extern char _binary_initrd_img_start[];
extern char _binary_initrd_img_end[];
extern char _binary_initrd_img_size[];
uint32_t EXT2_ADDRESS = _binary_initrd_img_start;

VFS *vfs;
Heap kernelHeap;
PhysicalPageAllocator kernelPageAllocator;
PhysicalPageAllocator userspacePageAllocator;
Gfx2DContext gfx;

extern uint32_t *gpu_flush(int args);

extern uint32_t GFX2D_BUFFER[1024 * 768];

void print_splash() {
    printf("   _____                       _   _       \n");
    printf("  / ____|                     | | (_)      \n");
    printf(" | (___  _   _ _ __   ___  ___| |_ _  __ _ \n");
    printf("  \\___ \\| | | | '_ \\ / _ \\/ __| __| |/ _` |\n");
    printf("  ____) | |_| | | | |  __/\\__ \\ |_| | (_| |\n");
    printf(" |_____/ \\__, |_| |_|\\___||___/\\__|_|\\__,_|\n");
    printf("          __/ |                            \n");
    printf("         |___/                          \n");
}

extern uint32_t open(const char *name, uint32_t flags, uint32_t mode);

extern uint32_t getpid();

uint32_t *window_dialog(int args) {
    uint32_t count = 0;
    GUIWindow window;
    gui_window_create(&window);
    window.component.size = SizeWH(340, 200);
    gui_window_init(&window, 10, 100, "Welcome");
    GUILabel label;
    gui_label_create(&label);
    label.component.size.width = 300;
    label.component.colorMode = TRANSPARENT;

    GUIButton buttonYes, buttonNo;
    gui_button_create(&buttonYes);
    gui_button_create(&buttonNo);

    gui_window_add_children(&window, &(label.component));
    gui_window_add_children(&window, &(buttonYes.component));
    gui_window_add_children(&window, &(buttonNo.component));
    while (1) {
        disable_interrupt();
        gui_label_init(&label, 0, 0, "hello, world! Is this cool?");
        gui_button_init(&buttonYes, 20, 50, "YES");
        gui_button_init(&buttonNo, 150, 50, "NO");
        gui_window_draw(&window);
        enable_interrupt();
    }
}

uint32_t *window_filesystem(int args) {
    GUIWindow window;
    gui_window_create(&window);
    window.component.size = SizeWH(340, 200);
    gui_window_init(&window, 380, 100, "FileManager");
    DirectoryEntry *directoryEntry = vfs->operations.lookup(vfs, "/initrd");
    struct GUILabel *labels;
    uint32_t size = 0;
    disable_interrupt();
    if (directoryEntry->children != nullptr) {
        size = klist_size(&directoryEntry->children->list);
        labels = (GUILabel *) kernelHeap.operations.alloc(&kernelHeap, size * sizeof(GUILabel));
        struct DirectoryEntry *pEntry = directoryEntry->children;
        uint32_t y = 0;
        for (uint32_t i = 1; i < size; i++) {
            gui_label_create(&labels[i]);
            gui_label_init(&labels[i], (i % 4) * 80, y * 20, pEntry->fileName);
            labels[i].component.colorMode = TRANSPARENT;
            gui_window_add_children(&window, &(labels[i].component));
            pEntry = getNode(pEntry->list.prev, DirectoryEntry, list);
            if (i % 4 == 0) {
                y++;
            }
        }
    }
    enable_interrupt();

    while (1) {
        disable_interrupt();
        uint32_t y = 0;
        for (uint32_t i = 1; i < size; i++) {
            labels[i].component.position.x = (i % 4) * 80;
            labels[i].component.position.y = y * 20;
            if (i % 4 == 0) {
                y++;
            }
        }
        gui_window_draw(&window);
        enable_interrupt();
    }
}


uint32_t *window_canvas2D(int args) {
    GUIWindow window;
    gui_window_create(&window);
    window.component.size = SizeWH(340, 200);
    gui_window_init(&window, 380, 360, "Canvas 2D Test Window");
    GUICanvas canvas;
    gui_canvas_create(&canvas);
    gui_canvas_init(&canvas, 0, 0);
    gui_window_add_children(&window, &(canvas.component));
    gui_canvas_fill_circle(&canvas, 30, 30, 20, 0x00FF0000);
    gui_canvas_fill_rect(&canvas, 60, 60, 100, 100, 0x0000FF00);
    gui_canvas_fill_triangle(&canvas, 10, 60, 60, 60, 10, 100, 0x0000FF);
    while (1) {
        disable_interrupt();
        gui_window_draw(&window);
        enable_interrupt();
    }
}


uint32_t *GPU_FLUSH(int args) {
    while (1) {
        disable_interrupt();
        gpu_flush(0);
        enable_interrupt();
    }
}

void initProcessUpdate(uint32_t process) {
    gfx.operations.fillRect(&gfx, 120, 520, 120 + process * (((1024 - 240) / 100) + 1), 530, 0xf25a29);

    gfx.operations.fillRect(&gfx, 120 - 10, 540, 1024 - 120, 570, 0x171520);
    GUILabel label;
    gui_label_create(&label);
    char str[10] = {'\0'};
    gui_label_init(&label, 120 + process * (((1024 - 240) / 100) + 1) - 8, 550, itoa(process, reinterpret_cast<char *>(&str), 10));
    GUILabel labelPercent;
    gui_label_create(&labelPercent);
    gui_label_init(&labelPercent, 120 + process * (((1024 - 240) / 100) + 1) + 8, 550, "%");
    gui_label_draw(&label);
    gui_label_draw(&labelPercent);
    gpu_flush(1);
}

TimerHandler gpuHandler;
SpinLock bootSpinLock = SpinLockCreate();

void renderBootScreen() {
    heap_create(&kernelHeap, &__HEAP_BEGIN, 64 * MB);
    gpu_init();

    kernel_vmm_add_map_hook(initProcessUpdate);

    gfx.operations.fillRect(&gfx, 0, 0, 1024, 768, 0x171520);
    gfx.operations.fillRect(&gfx, 120, 520, 1024 - 120, 530, 0xf7941d);

    gfx.operations.drawBitmap(&gfx, 384, 150, 256, 256, bootLogo());

    GUILabel label;
    gui_label_create(&label);
    label.component.colorMode = RGB;
    label.component.size.width = 100;
    gui_label_init(&label, 120, 500, "Booting...");
    gui_label_draw(&label);

    GUILabel labelCopyright;
    gui_label_create(&labelCopyright);
    gui_label_init(&labelCopyright, 450, 720, "@ZionLab 2020");
    gui_label_draw(&labelCopyright);
}

EXTERN_C void kernel_main(void) {
    if (read_cpuid() == 0) {
        bootSpinLock.operations.acquire(&bootSpinLock);
        init_bsp();
        print_splash();

        // create kernel physical page allocator
        page_allocator_create(&kernelPageAllocator, KERNEL_PHYSICAL_START, KERNEL_PHYSICAL_SIZE);

        gfx2d_create_context(&gfx, 1024, 768, GFX2D_BUFFER);
        renderBootScreen();

        // init kernel virtual memory mapping
        kernel_vmm_init();

        // create kernel heap
        heap_create(&kernelHeap, &__HEAP_BEGIN, KERNEL_PHYSICAL_SIZE - (uint32_t)(&__HEAP_BEGIN));

        // create userspace physical page allocator
        page_allocator_create(&userspacePageAllocator, USER_PHYSICAL_START, USER_PHYSICAL_SIZE);

        init_interrupt();

        vfs = vfs_create();

        vfs->operations.mount(vfs, "root", FILESYSTEM_EXT2, (void *) EXT2_ADDRESS);

        uint32_t *background = (uint32_t *) kernelHeap.operations.alloc(&kernelHeap, 768 * 1024 * 4);
        vfs_kernel_read(vfs, "/initrd/init/bg1024_768.dat", reinterpret_cast<char *>(background), 768 * 1024 * 4);
        gfx.operations.drawBitmap(&gfx, 0, 0, 1024, 768, background);
        kernelHeap.operations.free(&kernelHeap, background);

        gfx.operations.fillRect(&gfx, 0, 0, 1024, 64, FLUENT_PRIMARY_COLOR);
        GUILabel logo;
        logo.component.foreground = ColorRGB(0xFF, 0xFF, 0xFF);
        logo.component.colorMode = TRANSPARENT;
        gui_label_create(&logo);
        gui_label_init(&logo, 480, 28, "SynestiaOS (alpha 0.1.3)");
        gui_label_draw(&logo);

        schd_init();

        Thread *gpuProcess = thread_create("gpu", &GPU_FLUSH, 0, 0);
        schd_add_thread(gpuProcess, 1);

        Thread *cpuHolder = thread_create("cpuholder", &GPU_FLUSH, 0, 5);
        schd_add_thread(cpuHolder, 5);
        schd_add_thread(cpuHolder, 5);
        schd_add_thread(cpuHolder, 5);

        Thread *windowDialogThread = thread_create("Welcome", &window_dialog, 0, 0);
        schd_add_thread(windowDialogThread, 0);

        //        Thread *windowCanvas2DThread = thread_create("Canvas2D", &window_canvas2D, 1, 0);
        //        schd_add_thread(windowCanvas2DThread, 0);

        Thread *windowFileSystemThread = thread_create("FileManager", &window_filesystem, 0, 0);
        schd_add_thread(windowFileSystemThread, 0);


        bootSpinLock.operations.release(&bootSpinLock);
        schd_schedule();
    }

    // schd_switch_next();
}
