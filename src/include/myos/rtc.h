// Copyright 2022 Junbin Lei

#ifndef SRC_INCLUDE_MYOS_RTC_H_
#define SRC_INCLUDE_MYOS_RTC_H_

#include <myos/types.h>

void set_alarm(uint32 second);
uint8 cmos_read(uint8 addr);
void cmos_write(uint8 addr, uint8 value);

#endif  // SRC_INCLUDE_MYOS_RTC_H_
