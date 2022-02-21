#include <myos/myos.h>
#include <myos/types.h>
#include <myos/io.h>
#include <myos/string.h>
#include <myos/console.h>

char message[] = "Hello myos!!!\n";
char buf[1024];

void kernel_init()
{
    console_init();
    int count = 100000;
    while (count--)
    {
        console_write(message, sizeof(message) - 1);
    }
    return;
}