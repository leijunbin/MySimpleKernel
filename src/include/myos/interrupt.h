#ifndef MYOS_INTERRUPT_H
#define MYOS_INTERRUPT_H

#include <myos/types.h>

#define IDT_SIZE 256

typedef struct gate_t
{
    uint16 offset0;    // 段内偏移 0 ~ 15 位
    uint16 selector;   // 代码段选择子
    uint8 reserved;    // 保留不用
    uint8 type : 4;    // 任务门/中断门/陷阱门
    uint8 segment : 1; // segment = 0 表示系统段
    uint8 DPL : 2;     // 使用 int 指令访问的最低权限
    uint8 present : 1; // 是否有效
    uint16 offset1;    // 段内偏移 16 ~ 31 位
} _packed gate_t;

typedef void *handler_t;

void interrupt_init();

#endif