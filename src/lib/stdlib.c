// Copyright 2022 Junbin Lei

#include <myos/stdlib.h>

// 延迟
void delay(uint32 count) {
  while (count--) {
  }
}

// 阻塞函数
void hang() {
  while (true) {
  }
}

uint8 bcd_to_bin(uint8 value) { return (value & 0xf) + (value >> 4) * 10; }

uint8 bin_to_bcd(uint8 value) { return (value / 10) * 0x10 + (value % 10); }

// 计算num分成size的数量
uint32 div_round_up(uint32 num, uint32 size) { return (num + size - 1) / size; }
