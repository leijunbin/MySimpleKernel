[bits 32]

extern _Z11kernel_initv

global _start

_start:
    call _Z11kernel_initv
    jmp $
