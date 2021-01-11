//
// Created by XingfengYang on 2021/1/11.
//
#include "arm/register.h"
#include "arm/page.h"
#include "kernel/ext2.h"
#include "kernel/interrupt.h"
#include "kernel/kheap.h"
#include "kernel/percpu.h"
#include "kernel/scheduler.h"
#include "kernel/slab.h"
#include "kernel/vfs.h"
#include "libc/stdlib.h"
#include "libgui/gui_animation.h"
#include "libgui/gui_label.h"
#include "libgui/gui_window.h"
#include "libgui/gui_button.h"
#include "libgui/gui_canvas.h"
#include "libgui/gui_window.h"
#include "libc/string.h"


extern InterruptManager genericInterruptManager;
extern PhysicalPageAllocator kernelPageAllocator;
extern PhysicalPageAllocator userspacePageAllocator;
extern Heap kernelHeap;
extern Slab kernelObjectSlab;
extern Scheduler cfsScheduler;
extern VFS vfs;
extern GfxSurface mainSurface;

extern uint32_t open(const char *name, uint32_t flags, uint32_t mode);

extern uint32_t getpid();

_Noreturn uint32_t *window_dialog(int args) {
    uint32_t count = 0;
    GUIWindow window;
    gui_window_create(&window);
    window.component.size = SizeWH(340, 200);
    gui_window_init(&window, 10, 100, "Welcome");
    GUILabel label;
    gui_label_create(&label);
    label.component.size.width = 300;
    label.component.colorMode = TRANSPARENT;


    GUILabel label2;
    gui_label_create(&label2);
    label2.component.size.width = 300;
    label2.component.colorMode = TRANSPARENT;


    GUIButton buttonYes, buttonNo;
    gui_button_create(&buttonYes);
    gui_button_create(&buttonNo);

    gui_window_add_children(&window, &(label.component));
    gui_window_add_children(&window, &(label2.component));
    gui_window_add_children(&window, &(buttonYes.component));
    gui_window_add_children(&window, &(buttonNo.component));
    uint32_t i = 0;

    while (1) {
        genericInterruptManager.operation.disableInterrupt(&genericInterruptManager);
        gui_label_init(&label, 0, 0, "hello, world! Is this cool?");
        char buf[32];
        memset(buf, 0, 32);
        sprintf(buf, "%d", i++);
        gui_label_init(&label2, 80, 120, buf);
        gui_button_init(&buttonYes, 20, 50, "YES");
        gui_button_init(&buttonNo, 150, 50, "NO");
        gui_window_draw(&window);
        genericInterruptManager.operation.enableInterrupt(&genericInterruptManager);
    }
}

_Noreturn uint32_t *window_filesystem(int args) {
    GUIWindow window;
    gui_window_create(&window);
    window.component.size = SizeWH(340, 200);
    gui_window_init(&window, 380, 100, "FileManager");
    DirectoryEntry *directoryEntry = vfs.operations.lookup(&vfs, "/initrd");
    struct GUILabel *labels;
    uint32_t size = 0;
    genericInterruptManager.operation.disableInterrupt(&genericInterruptManager);
    if (directoryEntry->children != nullptr) {
        size = klist_size(&directoryEntry->children->list);
        labels = kernelHeap.operations.alloc(&kernelHeap, size * sizeof(GUILabel));
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
    genericInterruptManager.operation.enableInterrupt(&genericInterruptManager);

    while (1) {
        genericInterruptManager.operation.disableInterrupt(&genericInterruptManager);
        uint32_t y = 0;
        for (uint32_t i = 1; i < size; i++) {
            labels[i].component.position.x = (i % 4) * 80;
            labels[i].component.position.y = y * 20;
            if (i % 4 == 0) {
                y++;
            }
        }
        gui_window_draw(&window);
        genericInterruptManager.operation.enableInterrupt(&genericInterruptManager);
    }
}


_Noreturn uint32_t *window_canvas2D(int args) {
    GUIWindow window;
    gui_window_create(&window);
    window.component.size = SizeWH(340, 200);
    gui_window_init(&window, 380, 360, "Canvas 2D Test Window");
    GUICanvas canvas;
    gui_canvas_create(&canvas);
    gui_canvas_init(&canvas, 0, 0);
    gui_canvas_fill_circle(&canvas, 30, 30, 20, 0x00FF0000);
    gui_canvas_fill_rect(&canvas, 60, 60, 100, 100, 0x0000FF00);
    gui_canvas_fill_triangle(&canvas, 10, 60, 60, 60, 10, 100, 0x0000FF);

    gui_window_add_children(&window, &(canvas.component));
    while (1) {
        genericInterruptManager.operation.disableInterrupt(&genericInterruptManager);
        gui_window_draw(&window);
        genericInterruptManager.operation.enableInterrupt(&genericInterruptManager);
    }
}

void test_threads_init(){
    Thread *windowDialogThread = thread_create("Welcome", (ThreadStartRoutine) &window_dialog, 0, 0, svcModeCPSR());
    windowDialogThread->cpuAffinity = cpu_number_to_mask(0);
    cfsScheduler.operation.addThread(&cfsScheduler, windowDialogThread, 1);


    Thread *windowCanvas2DThread = thread_create("Canvas2D", (ThreadStartRoutine) &window_canvas2D, 0, 0,
                                                 svcModeCPSR());
    windowCanvas2DThread->cpuAffinity = cpu_number_to_mask(0);
    cfsScheduler.operation.addThread(&cfsScheduler, windowCanvas2DThread, 1);

    Thread *windowFileSystemThread = thread_create("FileManager", (ThreadStartRoutine) &window_filesystem, 0, 0,
                                                   svcModeCPSR());
    windowFileSystemThread->cpuAffinity = cpu_number_to_mask(0);
    cfsScheduler.operation.addThread(&cfsScheduler, windowFileSystemThread, 1);
}
