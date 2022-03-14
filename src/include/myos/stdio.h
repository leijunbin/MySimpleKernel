// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_STDIO_H_
#define SRC_INCLUDE_MYOS_STDIO_H_

#include <myos/stdarg.h>

int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);

#endif  // SRC_INCLUDE_MYOS_STDIO_H_
