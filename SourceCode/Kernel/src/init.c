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
#include <sched.h>
#include <stdlib.h>
#include <synestia_os_hal.h>
#include <vmm.h>

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
  while (1) {
    char str[10] = {'\0'};
    gui_label_init(&label, 0, 0, itoa(count, &str, 10));
    disable_interrupt();
    gui_window_draw(&window);
    enable_interrupt();
    count += 2;
  }
}

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
    gui_window_draw(&window);
    enable_interrupt();
    count++;
  }
}

extern uint32_t getpid();
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
    uint32_t pid = getpid();
    LogWarn("[Thread3] pid: %d .\n", pid);
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
//    gui_canvas_fill_circle(&canvas, 10, 10, 10, 0xFF0000);
    gui_window_draw(&window);
    enable_interrupt();
  }
}

TimerHandler gpuHandler;
void kernel_main(void) {
  print_splash();

  vmm_init();

  kheap_init();

  init_bsp();

  init_interrupt();

  gpu_init();
  Gfx2DContext context = {.width = 1024, .height = 768, .buffer = GFX2D_BUFFER};
  gfx2d_draw_bitmap(context, 0, 0, 1024, 768, desktop());
  draw_task_bar();

  gpuHandler.node.next = nullptr;
  gpuHandler.node.prev = nullptr;
  gpuHandler.timer_interrupt_handler = &gpu_flush;
  register_time_interrupt(&gpuHandler);

  schd_init();

  Thread *window1Thread = thread_create("window1", &window_thread1, 1, 1);
  schd_init_thread(window1Thread, 0);

  Thread *window2Thread = thread_create("window2", &window_thread2, 1, 1);
  schd_init_thread(window2Thread, 1);

  Thread *window3Thread = thread_create("window3", &window_thread3, 1, 1);
  schd_init_thread(window3Thread, 2);

  Thread *window4Thread = thread_create("window4", &window_thread4, 1, 1);
  schd_init_thread(window4Thread, 3);

  Thread *window5Thread = thread_create("window5", &window_thread5, 1, 1);
  schd_init_thread(window5Thread, 4);

  schd_schedule();
}