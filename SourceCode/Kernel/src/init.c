#include <cache.h>
#include <ext2.h>
#include <font8bits.h>
#include <gfx2d.h>
#include <gpu.h>
#include <gui_animation.h>
#include <gui_button.h>
#include <gui_canvas.h>
#include <gui_container.h>
#include <gui_label.h>
#include <gui_panel.h>
#include <gui_view3d.h>
#include <gui_window.h>
#include <interrupt.h>
#include <kheap.h>
#include <log.h>
#include <mutex.h>
#include <sched.h>
#include <spinlock.h>
#include <stdlib.h>
#include <string.h>
#include <synestia_os_hal.h>
#include <vfs.h>
#include <vmm.h>

extern char _binary_initrd_img_start[];
extern char _binary_initrd_img_end[];
extern char _binary_initrd_img_size[];
uint32_t EXT2_ADDRESS = _binary_initrd_img_start;
VFS *vfs;

extern uint32_t *gpu_flush(int args);

extern uint32_t GFX2D_BUFFER[1024 * 768];

void print_splash() {
  LogWarn("   _____                       _   _       \n");
  LogWarn("  / ____|                     | | (_)      \n");
  LogWarn(" | (___  _   _ _ __   ___  ___| |_ _  __ _ \n");
  LogWarn("  \\___ \\| | | | '_ \\ / _ \\/ __| __| |/ _` |\n");
  LogWarn("  ____) | |_| | | | |  __/\\__ \\ |_| | (_| |\n");
  LogWarn(" |_____/ \\__, |_| |_|\\___||___/\\__|_|\\__,_|\n");
  LogWarn("          __/ |                            \n");
  LogWarn("         |___/                          \n");
}

void draw_task_bar() {
  Gfx2DContext context = {.width = 1024, .height = 768, .buffer = GFX2D_BUFFER};
  gfx2d_fill_rect(context, 0, 0, 1024, 48, FLUENT_PRIMARY_COLOR);
  gfx2d_draw_logo(context, 8, 8, 0xFFFFFF);
}

extern uint32_t open(const char *name, uint32_t flags, uint32_t mode);

uint32_t *window_thread1(int args) {
  uint32_t count = 0;
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 300;
  window.component.size.height = 200;
  gui_window_init(&window, 20, 70, "window1");
  GUILabel label;
  gui_label_create(&label);
  label.component.colorMode = TRANSPARENT;
  label.component.size.width = 100;
  gui_window_add_children(&window, &(label.component));
  uint32_t fd = open("/initrd/bin/bin.txt", 1, 3);

  char *buffer = (char *)kheap_alloc(4);
  uint32_t size = vfs_kernel_read(vfs, "/initrd/bin/bin.txt", buffer, 3);
  buffer[3] = '\0';
  while (1) {
    char str[10] = {'\0'};
    gui_label_init(&label, 0, 0, itoa(count, &str, 10));
    disable_interrupt();
    LogWarn("[Thread3] fd: %d .\n", fd);
    LogWarn("[Thread3] data: %s .\n", buffer);
    gui_window_draw(&window);
    enable_interrupt();
    count += 2;
  }
}

extern uint32_t getpid();

uint32_t *window_thread2(int args) {
  uint32_t count = 0;
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 300;
  window.component.size.height = 200;
  gui_window_init(&window, 340, 70, "window2");
  GUILabel label;
  gui_label_create(&label);
  label.component.colorMode = TRANSPARENT;
  label.component.size.width = 100;
  gui_window_add_children(&window, &(label.component));
  while (1) {
    char str[10] = {'\0'};
    gui_label_init(&label, 0, 0, itoa(count, &str, 10));
    disable_interrupt();
    uint32_t pid = getpid();
    LogWarn("[Thread3] pid: %d .\n", pid);
    gui_window_draw(&window);
    enable_interrupt();
    count++;
  }
}

uint32_t *window_thread3(int args) {
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 620;
  window.component.size.height = 200;
  gui_window_init(&window, 20, 330, "Button Animation Test Window");
  GUIButton button;
  gui_button_create(&button);
  gui_button_init(&button, 0, 0, "TEST");
  gui_window_add_children(&window, &(button.component));

  GUIAnimationTranslation translation;
  gui_animation_translation_create(&translation, &(button.component), 10, 10, 0);

  while (1) {
    gui_button_init(&button, translation.currentX, translation.currentY, "TEST");
    gui_animation_update(&translation);
    disable_interrupt();
    gui_window_draw(&window);
    enable_interrupt();
  }
}

uint32_t *window_thread4(int args) {
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 340;
  window.component.size.height = 200;
  gui_window_init(&window, 660, 70, "Canvas 2D Test Window");
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

uint32_t *window_thread5(int args) {
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 340;
  window.component.size.height = 200;
  gui_window_init(&window, 660, 330, "View 3D Test Window");
  GUIView3D view;
  gui_view3d_create(&view);
  gui_view3d_init(&view, 0, 0);
  gui_window_add_children(&window, &(view.component));
  while (1) {
    disable_interrupt();
    gui_window_draw(&window);
    enable_interrupt();
  }
}

uint32_t *gpu(int args) {
  while (1) {
    disable_interrupt();
    gpu_flush(0);
    enable_interrupt();
  }
}

TimerHandler gpuHandler;
SpinLock bootSpinLock = SpinLockCreate();

void kernel_main(void) {
  if (read_cpuid() == 0) {
    bootSpinLock.operations.acquire(&bootSpinLock);
    init_bsp();
    print_splash();

    vmm_init();
    kheap_init();
    init_interrupt();

    Gfx2DContext context = {.width = 1024, .height = 768, .buffer = GFX2D_BUFFER};
    gfx2d_draw_bitmap(context, 0, 0, 1024, 768, desktop());
    draw_task_bar();

    schd_init();

    vfs = vfs_create();
    vfs->operations.mount(vfs, "root", FILESYSTEM_EXT2, (void *)EXT2_ADDRESS);

    Thread *window1Thread = thread_create("window1", &window_thread1, 1, 1);
    schd_add_thread(window1Thread, 1);

    Thread *window3Thread = thread_create("window3", &window_thread3, 1, 3);
    schd_add_thread(window3Thread, 1);

    Thread *window4Thread = thread_create("window4", &window_thread4, 1, 4);
    schd_add_thread(window4Thread, 1);

    Thread *window5Thread = thread_create("window5", &window_thread5, 1, 5);
    schd_add_thread(window5Thread, 5);

    Thread *window2Thread = thread_create("window2", &window_thread2, 1, 0);
    schd_add_thread(window2Thread, 0);

    Thread *gpuThread = thread_create("gpu", &gpu, 1, 0);
    schd_add_thread(gpuThread, 0);

    gpu_init();
    //    gpuHandler.node.next = nullptr;
    //    gpuHandler.node.prev = nullptr;
    //    gpuHandler.timer_interrupt_handler = &gpu_flush;
    //    register_time_interrupt(&gpuHandler);
    bootSpinLock.operations.release(&bootSpinLock);
    schd_schedule();
  }

  // schd_switch_next();
}
