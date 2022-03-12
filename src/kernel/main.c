#include <myos/myos.h>
#include <myos/io.h>
#include <myos/string.h>
#include <myos/console.h>
#include <myos/printk.h>
#include <myos/assert.h>
#include <myos/debug.h>
#include <myos/global.h>
#include <myos/task.h>
#include <myos/interrupt.h>

char message[] = "Hello myos!!!\n";
char buf[1024];

void kernel_init()
{
    console_init();
    gdt_init();
    interrupt_init();
    // task_init();
    return;
}