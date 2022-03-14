// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_TASK_H_
#define SRC_INCLUDE_MYOS_TASK_H_

#include <myos/types.h>

typedef uint32 target_t();

typedef struct task_t {
  uint32 *stack;  // 内核栈
} task_t;

typedef struct task_frame_t {
  uint32 edi;
  uint32 esi;
  uint32 ebx;
  uint32 ebp;
  void (*eip)(void);
} task_frame_t;

extern void task_switch(task_t *next);

void task_init();

#endif  // SRC_INCLUDE_MYOS_TASK_H_
