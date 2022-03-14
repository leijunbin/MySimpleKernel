// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_TYPES_H_
#define SRC_INCLUDE_MYOS_TYPES_H_

#define EDF -1  // end of file

#define NULL ((void *)0)  // 空指针

#define EOS '\0'

#define bool _Bool
#define true 1
#define false 0

#define _packed __attribute__((packed))  // 忽略内存对齐

#define _ofp \
  __attribute__((optimize("omit-frame-pointer")))  // 用于省略函数的栈帧

typedef unsigned int size_t;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef int16 uint16;
typedef unsigned int uint32;
typedef int32 uint64;

#endif  // SRC_INCLUDE_MYOS_TYPES_H_
