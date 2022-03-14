// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_ASSERT_H_
#define SRC_INCLUDE_MYOS_ASSERT_H_

void assertion_failure(char *exp, char *file, char *base, int line);

#define assert(exp) \
  if (exp)          \
    ;               \
  else              \
    assertion_failure(#exp, __FILE__, __BASE_FILE__, __LINE__)

void panic(const char *fmt, ...);

#endif  // SRC_INCLUDE_MYOS_ASSERT_H_
