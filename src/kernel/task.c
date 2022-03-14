// Copyright 2022 Junbin Lei

#include <myos/printk.h>
#include <myos/task.h>

#define PAGE_SIZE 0x1000

task_t *a = (task_t *)0x5000;
task_t *b = (task_t *)0x6000;

task_t *running_task() {
  asm volatile(
      "mov %esp, %eax\n"
      "andl $0xfffff000, %eax\n");
}

void schedule() {
  task_t *current = running_task();
  task_t *next = current == a ? b : a;
  task_switch(next);
}

uint32 _ofp thread_a() {
  asm volatile("sti\n");

  while (true) {
    printk("A");
  }
}

uint32 _ofp thread_b() {
  asm volatile("sti\n");

  while (true) {
    printk("B");
  }
}

static void task_create(task_t *task, target_t target) {
  uint32 stack = (uint32)task + PAGE_SIZE;
  stack -= sizeof(task_frame_t);
  task_frame_t *frame = (task_frame_t *)stack;
  frame->ebx = 0x11111111;
  frame->esi = 0x22222222;
  frame->edi = 0x33333333;
  frame->ebp = 0x44444444;
  frame->eip = (void *)target;

  task->stack = (uint32 *)stack;
}

void task_init() {
  task_create(a, thread_a);
  task_create(b, thread_b);
  schedule();
}
