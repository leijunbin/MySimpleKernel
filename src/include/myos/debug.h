// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_DEBUG_H_
#define SRC_INCLUDE_MYOS_DEBUG_H_

void debugk(char *file, int line, const char *fmt, ...);

#define DEBUGK(fmt, args...) debugk(__BASE_FILE__, __LINE__, fmt, ##args)

#endif  // SRC_INCLUDE_MYOS_DEBUG_H_
