// Copyright 2022 Junbin Lei

#include <myos/string.h>
#include <myos/types.h>

char *strcpy(char *dest, const char *src) {
  char *ptr = dest;
  while (true) {
    *ptr++ = *src;
    if (*src++ == EOS) return dest;
  }
}

char *strcat(char *dest, const char *src) {
  char *ptr = dest;
  while (*ptr != EOS) {
    ptr++;
  }
  while (true) {
    *ptr++ = *src;
    if (*src++ == EOS) {
      return dest;
    }
  }
}

size_t strlen(const char *str) {
  char *ptr = (char *)str;
  while (*ptr != EOS) {
    ptr++;
  }
  return ptr - str;
}

int strcmp(const char *lhs, const char *rhs) {
  char *lptr = (char *)lhs;
  char *rptr = (char *)rhs;
  while (*lptr == *rptr && *lptr != EOS && *rptr != EOS) {
    lptr++, rptr++;
  }
  return *lptr < *rptr ? -1 : *lptr > *rptr;
}

char *strchr(const char *str, int ch) {
  char *ptr = (char *)str;
  while (true) {
    if (*ptr == ch) {
      return ptr;
    }
    if (*ptr++ == EOS) {
      return NULL;
    }
  }
}

char *strrchr(const char *str, int ch) {
  char *last = NULL;
  char *ptr = (char *)str;
  while (true) {
    if (*ptr == ch) {
      last = ptr;
    }
    if (*ptr++ == EOS) {
      return last;
    }
  }
}

int memcmp(const void *lhs, const void *rhs, size_t count) {
  char *lptr = (char *)lhs;
  char *rptr = (char *)rhs;
  while (*lptr == *rptr && count-- > 0) {
    lptr++;
    rptr++;
  }
  return *lptr < *rptr ? -1 : *lptr > *rptr;
}

void *memset(void *dest, int ch, size_t count) {
  char *ptr = dest;
  while (count--) {
    *ptr++ = ch;
  }
  return dest;
}

void *memcpy(void *dest, const void *src, size_t count) {
  char *ptr = dest;
  char *srcp = (void *)src;
  while (count--) {
    *ptr++ = *srcp++;
  }
  return dest;
}

void *memchr(const void *str, int ch, size_t count) {
  char *ptr = (void *)str;
  while (count--) {
    if (*ptr == ch) {
      return ptr;
    }
    ptr++;
  }
  return NULL;
}
