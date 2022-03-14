// Copyright 2022 Junbin Lei

#include <myos/assert.h>
#include <myos/console.h>
#include <myos/debug.h>
#include <myos/global.h>
#include <myos/interrupt.h>
#include <myos/io.h>
#include <myos/myos.h>
#include <myos/printk.h>
#include <myos/stdlib.h>
#include <myos/string.h>
#include <myos/task.h>

char message[] = "Hello myos!!!\n";
char buf[1024];

void kernel_init() {
  console_init();
  gdt_init();
  interrupt_init();
  task_init();
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
