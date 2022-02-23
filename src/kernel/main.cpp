#include <myos/myos.h>
#include <myos/io.h>
#include <myos/string.h>
#include <myos/console.h>
#include <myos/printk.h>

char message[] = "Hello myos!!!\n";
char buf[1024];

void kernel_init()
{
    console_init();
    int cnt = 30;
    while (cnt--)
    {
        printk("Hello myos %#010x\n", cnt);
    }
    return;
}