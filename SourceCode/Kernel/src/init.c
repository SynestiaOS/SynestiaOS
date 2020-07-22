#include <font8bits.h>
#include <gfx2d.h>
#include <gpu.h>
#include <gui_animation.h>
#include <gui_button.h>
#include <gui_canvas.h>
#include <gui_container.h>
#include <gui_label.h>
#include <gui_panel.h>
#include <gui_window.h>
#include <interrupt.h>
#include <kheap.h>
#include <sched.h>
#include <stdlib.h>
#include <synestia_os_hal.h>
#include <vmm.h>
#include <log.h>

extern uint32_t *gpu_flush(int args);

void print_splash() {
  LogWarnning("   _____                       _   _       \n");
  LogWarnning("  / ____|                     | | (_)      \n");
  LogWarnning(" | (___  _   _ _ __   ___  ___| |_ _  __ _ \n");
  LogWarnning("  \\___ \\| | | | '_ \\ / _ \\/ __| __| |/ _` |\n");
  LogWarnning("  ____) | |_| | | | |  __/\\__ \\ |_| | (_| |\n");
  LogWarnning(" |_____/ \\__, |_| |_|\\___||___/\\__|_|\\__,_|\n");
  LogWarnning("          __/ |                            \n");
  LogWarnning("         |___/                          \n");
}

void draw_task_bar() {
  uint32_t *barBuffer = (uint32_t *)kheap_alloc(1024 * 32 * 4);

  for (int i = 0; i < 1024; i++) {
    for (int j = 0; j < 31; j++) {
      barBuffer[j * 1024 + i] = ((FLUENT_PRIMARY_COLOR >> 16) & 0xFF - j) << 16 |
                                ((FLUENT_PRIMARY_COLOR >> 8) & 0xFF - j) << 8 | (FLUENT_PRIMARY_COLOR & 0xFF - j);
    }
  }
  for (int i = 0; i < 1024; i++) {
    barBuffer[31 * 1024 + i] = 0x999999;
  }
  gfx2d_draw_bitmap(0, 0, 1024, 32, barBuffer);
  gfx2d_draw_logo(0, 0, 0xFFFFFF);
}

uint32_t *window_thread1(int args) {
  uint32_t count = 0;
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 510;
  window.component.size.height = 500;
  gui_window_init(&window, 0, 33, "window1");
  GUILabel label;
  gui_label_create(&label);
  label.component.foreground.r = 0x00;
  label.component.foreground.g = 0x00;
  label.component.foreground.b = 0x00;
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
  window.component.size.width = 510;
  window.component.size.height = 500;
  gui_window_init(&window, 512, 33, "window2");
  GUILabel label;
  gui_label_create(&label);
  label.component.foreground.r = 0x00;
  label.component.foreground.g = 0x00;
  label.component.foreground.b = 0x00;
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

uint32_t *window_thread3(int args) {
  GUIWindow window;
  gui_window_create(&window);
  window.component.size.width = 1022;
  window.component.size.height = 150;
  gui_window_init(&window, 0, 560, "window3");
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

TimerHandler gpuHandler;
void kernel_main(void) {

  print_splash();

  vmm_init();

  kheap_init();

  init_bsp();

  init_interrupt();

  gpu_init();
  gfx2d_draw_bitmap(0, 0, 1024, 768, desktop());
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

  schd_schedule();
}