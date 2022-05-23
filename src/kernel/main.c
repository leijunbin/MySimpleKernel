// Copyright 2022 Junbin Lei

extern void memory_map_init();
extern void interrupt_init();
extern void clock_init();
extern void hang();
extern void time_init();
extern void rtc_init();

extern void memory_test();

void kernel_init() {
  memory_map_init();

  interrupt_init();
  clock_init();
  // time_init();
  // rtc_init();

  memory_test();
  asm volatile("sti");
  hang();

  // task_init();
  // asm volatile(
  //     "sti\n"
  //     "movl %eax, %eax\n");

  // uint32 counter = 0;
  // while (true) {
  //   DEBUGK("looping in kernel init %d...\n", counter++);
  //   delay(100000000);
  // }

  return;
}
