# 操作系统——断言assert、调试工具、内核的全局描述符表

## 断言assert

用于确定程序的运行状态，防止错误蔓延！！！

并且提供尽可能多的出错信息，以供排错。

## 调试工具
```c++
DEBUGK();
```
## 内核的全局描述符表

```c++
descriptor_t gdt[GDT_SIZE]; // 内核全局描述符表
pointer_t gdt_ptr;          // 内核全局描述符表指针
```

```s
lgdt [gdt_ptr]; 加载 gdt
sgdt [gdt_ptr]; 保存 gdt
```

## 参考文献

+ <https://en.cppreference.com/w/cpp/error/assert>

+ <https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html>
+ <https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html>
