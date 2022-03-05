[bits 32]

section .text

global inb ; 端口输入一个字节
inb  :
    push ebp
    mov ebp, esp  ; 保存栈帧

    xor eax, eax
    mov edx, [ebp + 8] ; port
    in al, dx ; 将端口号dx的8bit输入到al

    jmp $+2
    jmp $+2
    jmp $+2

    leave ; 恢复栈帧
    ret

global outb ; CPU输出一个字节
outb:
    push ebp
    mov ebp, esp  ; 保存栈帧

    mov edx, [ebp + 8] ;port
    mov eax, [ebp + 12] ;value
    out dx, al ; 将al输出到端口号dx的端口

    jmp $+2
    jmp $+2
    jmp $+2

    leave ; 恢复栈帧
    ret

global _inw ; 端口输入一个字节
inw:
    push ebp
    mov ebp, esp  ; 保存栈帧

    xor eax, eax
    mov edx, [ebp + 8] ; port
    in ax, dx ; 将端口号dx的8bit输入到ax

    jmp $+2
    jmp $+2
    jmp $+2

    leave ; 恢复栈帧
    ret

global outw ; CPU输出一个字节
outw:
    push ebp
    mov ebp, esp  ; 保存栈帧

    mov edx, [ebp + 8] ;port
    mov eax, [ebp + 12] ;value
    out dx, ax ; 将ax输出到端口号dx的端口

    jmp $+2
    jmp $+2
    jmp $+2

    leave ; 恢复栈帧
    ret
