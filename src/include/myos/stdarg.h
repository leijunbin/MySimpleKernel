// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_STDARG_H_
#define SRC_INCLUDE_MYOS_STDARG_H_

typedef char *va_list;

#define va_start(ap, v) (ap = (va_list)&v + sizeof(char *))
#define va_arg(ap, t) (*(t *)((ap += sizeof(char *)) - sizeof(char *)))
#define va_end(ap) (ap = (va_list)0)

#endif  // SRC_INCLUDE_MYOS_STDARG_H_
