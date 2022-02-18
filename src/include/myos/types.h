#ifndef MYOS_TYPES_H
#define MYOS_TYPES_H

#define EDF -1 // end of file

#define NULL 0 //空指针

#define bool _Bool
#define true 1
#define false 0

#define _packed __attribute__((packed)) //忽略内存对齐

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#endif