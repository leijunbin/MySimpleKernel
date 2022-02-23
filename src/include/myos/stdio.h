#ifndef MYOS_STDIO_H
#define MYOS_STDIO_H

#include <myos/stdarg.h>

int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);

#endif