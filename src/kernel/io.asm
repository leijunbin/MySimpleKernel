[bits 32]

section .text

global _Z3inbt ; 端口输入一个字节
_Z3inbt:
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

global _Z4outbth ; CPU输出一个字节
_Z4outbth:
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

global _Z3inwt ; 端口输入一个字节
_Z3inwt:
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

global _Z4outwtt ; CPU输出一个字节
_Z4outwtt:
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
