// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_STDLIB_H_
#define SRC_INCLUDE_MYOS_STDLIB_H_

#include <myos/types.h>

void delay(uint32 count);
void hang();

uint8 bcd_to_bin(uint8 value);
uint8 bin_to_bcd(uint8 value);

#endif  // SRC_INCLUDE_MYOS_STDLIB_H_
