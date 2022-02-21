#include <myos/types.h>
#include <myos/console.h>
#include <myos/io.h>
#include <myos/string.h>

#define CRT_ADDR_REG 0x3D4 // CRT(6845)索引寄存器
#define CRT_DATE_REG 0x3D5 // CRT(6845)数据寄存器

#define CRT_START_ADDR_H 0xC // 显示内存地址位置 - 高位
#define CRT_START_ADDR_L 0xD // 显示内存地址位置 - 低位
#define CRT_CURSOR_H 0xE     // 光标位置 - 高位
#define CRT_CURSOR_L 0xF     // 光标位置 - 低位

#define MEM_BASE 0xB8000              // 显卡内存开始位置
#define MEM_SIZE 0x4000               // 显卡内存大小
#define MEM_END (MEM_BASE + MEM_SIZE) // 显卡内存结束位置
#define WIDTH 80                      // 屏幕文本列数
#define HEIGHT 25                     // 屏幕文本行数
#define ROW_SIZE (WIDTH * 2)          // 每行字节数
#define SCR_SIZE (ROW_SIZE * HEIGHT)  // 屏幕字节数

#define ASCII_NUL 0x00
#define ASCII_ENQ 0x05
#define ASCII_BEL 0x07 // \a
#define ASCII_BS 0x08  // \b
#define ASCII_HT 0x09  // \t
#define ASCII_LF 0x0A  // \n
#define ASCII_VT 0x0B  // \v
#define ASCII_FF 0x0C  // \f
#define ASCII_CR 0x0D  // \r
#define ASCII_DEL 0x7F

static uint32 screen; // 当前显示器开始的内存位置

static uint32 pos; // 记录当前光标的内存位置

static uint32 x, y; // 记录当前光标的坐标

static uint8 attr = 7;        // 字符样式
static uint16 erase = 0x0720; // 带样式的空格

// 获取当前显示器显存的开始位置
static void get_screen()
{
    outb(CRT_ADDR_REG, CRT_START_ADDR_H); // 开始位置高地址
    screen = inb(CRT_DATE_REG) << 8;      // 开始位置高8位
    outb(CRT_ADDR_REG, CRT_START_ADDR_L); // 开始位置低地址
    screen |= inb(CRT_DATE_REG);          // 开始位置低8位

    screen <<= 1;
    screen += MEM_BASE;
}

// 设置当前显示器显存的开始位置
static void set_screen()
{
    outb(CRT_ADDR_REG, CRT_START_ADDR_H); // 开始位置高地址
    outb(CRT_DATE_REG, ((screen - MEM_BASE) >> 9) & 0xff);

    outb(CRT_ADDR_REG, CRT_START_ADDR_L); // 开始位置低地址
    outb(CRT_DATE_REG, ((screen - MEM_BASE) >> 1) & 0xff);
}

// 获取当前光标位置
static void get_cursor()
{
    outb(CRT_ADDR_REG, CRT_CURSOR_H); // 光标位置高8位
    pos = inb(CRT_DATE_REG) << 8;
    outb(CRT_ADDR_REG, CRT_CURSOR_L); // 光标位置低8位
    pos |= inb(CRT_DATE_REG);

    get_screen();

    pos <<= 1;
    pos += MEM_BASE;

    uint32 delta = (pos - screen) >> 1;
    x = delta % WIDTH;
    y = delta / WIDTH;
}

// 设置当前光标位置
static void set_cursor()
{
    outb(CRT_ADDR_REG, CRT_CURSOR_H); // 光标位置高8位
    outb(CRT_DATE_REG, ((pos - MEM_BASE) >> 9) & 0xff);

    outb(CRT_ADDR_REG, CRT_CURSOR_L); // 光标位置低8位
    outb(CRT_DATE_REG, ((pos - MEM_BASE) >> 1) & 0xff);
}

// 清空屏幕
void console_clear()
{
    screen = MEM_BASE;
    pos = MEM_BASE;
    x = y = 0;
    set_cursor();
    set_screen();

    uint16 *ptr = (uint16 *)MEM_BASE;
    while (ptr < (uint16 *)MEM_END)
    {
        *ptr++ = erase;
    }
}

// 向上滚屏
static void scroll_up()
{
    if (screen + SCR_SIZE + ROW_SIZE < MEM_END)
    {
        uint32 *ptr = (uint32 *)(screen + SCR_SIZE);
        for (size_t i = 0; i < WIDTH; i++)
        {
            *ptr++ = erase;
        }
        screen += ROW_SIZE;
        pos += ROW_SIZE;
    }
    else
    {
        memcpy((void *)MEM_BASE, (void *)screen, SCR_SIZE);
        pos -= (screen - MEM_BASE);
        screen = MEM_BASE;
    }
    set_screen();
}

// 此代码导致一个回车或换行操作
static void command_lf()
{
    if (y + 1 < HEIGHT)
    {
        y++;
        pos += ROW_SIZE;
        return;
    }
    scroll_up();
}

// 将光标移到当前行的左边缘处
static void command_cr()
{
    pos -= (x << 1);
    x = 0;
}

// 将光标移向左边一个字符位置处；若光标已经处在左边沿，则无动作
static void command_bs()
{
    if (x)
    {
        x--;
        pos -= 2;
        *(uint16 *)pos = erase;
    }
}

// 在输入时忽略 不保存在输入缓冲中
static void command_del()
{

    *(uint16 *)pos = erase;
}

void console_write(char *buf, uint32 count)
{
    char ch;
    char *ptr = (char *)pos;
    while (count--)
    {
        ch = *buf++;
        switch (ch)
        {
        case ASCII_NUL:
            break;
        case ASCII_ENQ:
            break;
        case ASCII_BEL:
            // todo \a
            break;
        case ASCII_BS:
            command_bs();
            break;
        case ASCII_HT:
            break;
        case ASCII_LF:
            command_lf();
            command_cr();
            break;
        case ASCII_VT:
            break;
        case ASCII_FF:
            command_lf();
            break;
        case ASCII_CR:
            command_cr();
            break;
        case ASCII_DEL:
            command_del();
            break;
        default:
            if (x >= WIDTH)
            {
                x -= WIDTH;
                pos -= ROW_SIZE;
                command_lf();
            }
            *ptr = ch;
            ptr++;
            *ptr = attr;
            ptr++;

            pos += 2;
            x++;
            break;
        }
    }
    set_cursor();
}

void console_init()
{
    console_clear();
}