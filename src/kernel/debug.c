// Copyright 2022 Junbin Lei

#include <myos/debug.h>
#include <myos/printk.h>
#include <myos/stdarg.h>
#include <myos/stdio.h>

static char buf[1024];

void debugk(char *file, int line, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);

  printk("[%s] [%d] %s", file, line, buf);
}
