// Copyright 2022 Junbin Lei

#include <myos/debug.h>
#include <myos/io.h>
#include <myos/rtc.h>
#include <myos/stdlib.h>
#include <myos/time.h>

#define CMOS_ADDR 0x70  // CMOS 地址寄存器
#define CMOS_DATA 0x71  // CMOS 数据寄存器

// 下面是 CMOS 信息的寄存器索引
#define CMOS_SECOND 0x00   // (0 ~ 59)
#define CMOS_MINUTE 0x02   // (0 ~ 59)
#define CMOS_HOUR 0x04     // (0 ~ 23)
#define CMOS_WEEKDAY 0x06  // (1 ~ 7) 星期天 = 1，星期六 = 7
#define CMOS_DAY 0x07      // (1 ~ 31)
#define CMOS_MONTH 0x08    // (1 ~ 12)
#define CMOS_YEAR 0x09     // (0 ~ 99)
#define CMOS_CENTURY 0x32  // 可能不存在
#define CMOS_NMI 0x80

#define MINUTE 60           // 每分钟的秒数
#define HOUR (60 * MINUTE)  // 每小时的秒数
#define DAY (24 * HOUR)     // 每天的秒数
#define YEAR (365 * DAY)    // 每年的秒数，以 365 天算

// 每个月开始时的已经过去天数
static int month[13] = {0,  // 这里占位，没有 0 月，从 1 月开始
                        0,
                        (31),
                        (31 + 29),
                        (31 + 29 + 31),
                        (31 + 29 + 31 + 30),
                        (31 + 29 + 31 + 30 + 31),
                        (31 + 29 + 31 + 30 + 31 + 30),
                        (31 + 29 + 31 + 30 + 31 + 30 + 31),
                        (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31),
                        (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30),
                        (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31),
                        (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30)};

time_t startup_time;
int century;

time_t mktime(tm *time) {
  time_t res;
  int year;

  // 1970年开始的年份
  if (time->tm_year >= 70) {
    year = time->tm_year - 70;
  } else {
    year = time->tm_year - 70 + 100;
  }

  res = YEAR * year;
  res += DAY * ((year + 1) / 4);
  res += month[time->tm_mon] * DAY;
  if (time->tm_mon > 2 && ((year + 2) % 4)) res -= DAY;
  res += DAY * (time->tm_mday - 1);
  res += HOUR * time->tm_hour;
  res += MINUTE * time->tm_min;
  res += time->tm_sec;
  return res;
}

int get_yday(tm *time) {
  int res = month[time->tm_mon];
  res += time->tm_mday;
  int year;

  if (time->tm_year >= 70) {
    year = time->tm_year - 70;
  } else {
    year = time->tm_year - 70 + 100;
  }

  if ((year + 2) % 4 && time->tm_mon > 2) {
    res -= 1;
  }

  return res;
}

void time_read_bcd(tm *time) {
  do {
    time->tm_sec = cmos_read(CMOS_SECOND);
    time->tm_min = cmos_read(CMOS_MINUTE);
    time->tm_hour = cmos_read(CMOS_HOUR);
    time->tm_wday = cmos_read(CMOS_WEEKDAY);
    time->tm_mday = cmos_read(CMOS_DAY);
    time->tm_mon = cmos_read(CMOS_MONTH);
    time->tm_year = cmos_read(CMOS_YEAR);
    century = cmos_read(CMOS_CENTURY);
  } while (time->tm_sec != cmos_read(CMOS_SECOND));
}

void time_read(tm *time) {
  time_read_bcd(time);
  time->tm_sec = bcd_to_bin(time->tm_sec);
  time->tm_min = bcd_to_bin(time->tm_min);
  time->tm_hour = bcd_to_bin(time->tm_hour);
  time->tm_wday = bcd_to_bin(time->tm_wday);
  time->tm_mday = bcd_to_bin(time->tm_mday);
  time->tm_mon = bcd_to_bin(time->tm_mon);
  time->tm_year = bcd_to_bin(time->tm_year);
  time->tm_yday = get_yday(time);
  time->tm_isdst = -1;
  century = bcd_to_bin(century);
}

void time_init() {
  tm time;
  time_read(&time);
  startup_time = mktime(&time);
  DEBUGK("startup time: %d%d-%02d-%02d %02d:%02d:%02d\n", century, time.tm_year,
         time.tm_mon, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}
