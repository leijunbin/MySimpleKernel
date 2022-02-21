#ifndef MYOS_CONSOLE_H
#define MYOS_CONSOLE_H

#include <myos/types.h>

void console_init();                         // 屏幕初始化
void console_clear();                        // 屏幕清空
void console_write(char *buf, uint32 count); //显示字符串

#endif