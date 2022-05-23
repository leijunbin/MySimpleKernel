// Copyright 2022 Junbin Lei

#include <myos/assert.h>
#include <myos/debug.h>
#include <myos/memory.h>
#include <myos/stdlib.h>
#include <myos/string.h>
#include <myos/types.h>

#define ZONE_VALID 1     // ards可用内存区域
#define ZONE_RESERVED 2  // ards不可用区域

#define IDX(addr) ((uint32)addr >> 12)  // 获取addr的页索引
#define PAGE(idx) ((uint32)idx << 12)  // 获取页索引idx对应页开始的位置
#define ASSERT_PAGE(addr) assert((addr & 0xfff) == 0)

typedef struct ards_t {
  uint64 base;  // 内存基地址
  uint64 size;  // 内存长度
  uint32 type;  // 类型
} _packed ards_t;

static uint32 memory_base = 0;  // 可用内存基地址，应该等于1M
static uint32 memory_size = 0;  // 可用内存大小
static uint32 total_pages = 0;  // 所有内存页数
static uint32 free_pages = 0;   // 空闲内存页数

#define used_pages (total_pages - free_pages)  // 已用页数

void memory_init(uint32 magic, uint32 addr) {
  uint32 count;
  ards_t *ptr;

  if (magic == ONIX_MAGIC) {
    count = *(uint32 *)(addr);
    ptr = (ards_t *)(addr + 4);
    for (size_t i = 0; i < count; i++, ptr++) {
      DEBUGK("Memory base 0x%p size 0x%p type %d\n", (uint32)ptr->base,
             (uint32)ptr->size, (uint32)ptr->type);
      if (ptr->type == ZONE_VALID && ptr->size > memory_size) {
        memory_base = (uint32)ptr->base;
        memory_size = (uint32)ptr->size;
      }
    }
  } else {
    panic("Memory init magic unknown 0x%p\n", magic);
  }

  DEBUGK("ARDS count %d\n", count);
  DEBUGK("Memory base 0x%p\n", (uint32)memory_base);
  DEBUGK("Memory size 0x%p\n", (uint32)memory_size);

  total_pages = IDX(memory_size) + IDX(MEMORY_BASE);
  free_pages = IDX(memory_size);

  DEBUGK("Total pages %d\n", total_pages);
  DEBUGK("Free pages %d\n", free_pages);
}

static uint32 start_page = 0;    // 可分配物理内存起始位置
static uint8 *memory_map;        // 物理内存数组
static uint32 memory_map_pages;  // 物理内存占用的页数

void memory_map_init() {
  memory_map = (uint8 *)memory_base;
  memory_map_pages = div_round_up(total_pages, PAGE_SIZE);
  DEBUGK("Memory map page count %d\n", memory_map_pages);
  free_pages -= memory_map_pages;

  // 清空物理内存数组
  memset((void *)memory_map, 0, memory_map_pages * PAGE_SIZE);

  // 前1M的内存位置以及物理内存数组已占用的页
  start_page = IDX(MEMORY_BASE) + memory_map_pages;
  for (size_t i = 0; i < start_page; i++) {
    memory_map[i] = 1;
  }

  DEBUGK("Total pages %d free pages %d\n", total_pages, free_pages);
}

// 分配一页物理内存
static uint32 get_page() {
  for (size_t i = start_page; i < total_pages; i++) {
    // 如果物理内存没有占用
    if (!memory_map[i]) {
      memory_map[i] = 1;
      free_pages--;
      assert(free_pages >= 0);
      uint32 page = PAGE(i);
      DEBUGK("GET page 0x%p\n", page);
      return page;
    }
  }
  panic("Out of Memory!!!");
}

// 释放一页物理内存
static void put_page(uint32 addr) {
  ASSERT_PAGE(addr);
  uint32 idx = IDX(addr);
  // idx大于1M并且小于总页面树
  assert(idx >= start_page && idx < total_pages);
  // 保证页面被应用
  assert(memory_map[idx] >= 1);
  memory_map[idx]--;
  if (!memory_map[idx]) {
    free_pages++;
  }
  assert(free_pages > 0 && free_pages < total_pages);
  DEBUGK("PUT page 0x%p\n", addr);
}

void memory_test() {
  uint32 pages[10];
  for (size_t i = 0; i < 10; i++) {
    pages[i] = get_page();
  }
  for (size_t i = 0; i < 10; i++) {
    put_page(pages[i]);
  }
}
