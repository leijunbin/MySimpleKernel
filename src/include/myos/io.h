#ifndef MYOS_IO_H
#define MYOS_IO_H

#include <myos/types.h>

extern uint8 inb(uint16 port);  // 端口输入一个字节
extern uint16 inw(uint16 port); // 端口输入一个字

extern void outb(uint16 port, uint8 value);  // CPU输出一个字节
extern void outw(uint16 port, uint16 value); // CPU输出一个字

#endif