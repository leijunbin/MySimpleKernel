// Copyright 2022 Junbin Lei

extern void console_init();
extern void gdt_init();
extern void interrupt_init();
extern void clock_init();
extern void hang();
extern void time_init();
extern void rtc_init();

void kernel_init() {
  console_init();
  gdt_init();
  interrupt_init();
  clock_init();
  time_init();
  rtc_init();

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
