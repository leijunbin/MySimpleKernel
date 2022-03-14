// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_STRING_H_
#define SRC_INCLUDE_MYOS_STRING_H_

#include <myos/types.h>

char *strcpy(char *dest, const char *src);     // 复制字符串
char *strcat(char *dest, const char *src);     // 拼接字符串
size_t strlen(const char *str);                // 字符串长度
int strcmp(const char *lhs, const char *rhs);  // 字符串比较
char *strchr(const char *str, int ch);  // 字符串中查找某个字符第一次出现位置
char *strrchr(const char *str, int ch);  // 字符串中查找某个字符最后一次出现位置
int memcmp(const void *lhs, const void *rhs,
           size_t count);  // 比较指定数量字符串大小
void *memset(void *dest, int ch,
             size_t count);  // 将前一定数量的字符设置为一个字符
void *memcpy(void *dest, const void *src, size_t count);  // 拷贝count字节结束
void *memchr(const void *str, int ch, size_t count);  // 在一定范围内寻找字符

#endif  // SRC_INCLUDE_MYOS_STRING_H_
