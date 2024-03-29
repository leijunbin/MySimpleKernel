[org 0x1000]

dw 0x55aa ;用于判断错误

mov si, loading
call print

detect_memory:
    ; ebx置为0
    xor ebx, ebx
    
    ; es:di 结构体缓存位置
    mov ax, 0
    mov es, ax
    mov edi, ards_buffer

    mov edx, 0x534d4150 ;固定签名

.next:
    ; 子功能号
    mov eax, 0xe820
    ; ards结构大小（字节）
    mov ecx, 20

    int 0x15

    ; 出错跳转
    jc error

    add di, cx

    ; 结构体数量加一
    inc dword [ards_count]

    cmp ebx, 0
    jnz .next

    mov si, detecting
    call print

prepare_protected_mode:
    
    cli ;关闭中断

    in al, 0x92
    or al, 0b10
    out 0x92, al ;打开A20线

    lgdt [gdt_ptr] ;加载gdt

    mov eax, cr0
    or eax, 1
    mov cr0, eax ;启动保护模式

    jmp dword code_selector:protected_mode ;利用跳转刷新缓存，启用保护模式

print:
    mov ah, 0x0e
    .next:
        mov al, [si]
        cmp al, 0
        jz .done
        int 0x10
        inc si
        jmp .next
    .done:
        ret

error:
    mov si, .msg
    call print
    hlt ;CPU停机
    jmp $
    .msg:
        db "Loading Error!!!", 10, 13, 0 ;\n\r\0

[bits 32]
protected_mode:
    mov ax, date_selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax ;初始化段寄存器

    mov esp, 0x10000 ;修改栈顶

    mov edi, 0x10000 ;目标内存
    mov ecx, 10 ;起始扇区编号
    mov bl, 200 ;扇区数量

    call read_disk ; 读取内核

    mov eax, 0x20220205 ; 内核魔数
    mov ebx, ards_count ; ards 数量指针

    jmp dword code_selector:0x10000 

read_disk:
    ;设置读写扇区数量
    mov dx, 0x1f2
    mov al, bl
    out dx, al

    inc dx ;0x1f3
    mov al, cl ;起始扇区编号低8位
    out dx, al

    inc dx ;0x1f4
    shr ecx, 8
    mov al, cl ;起始扇区编号中8位
    out dx, al
    
    inc dx ;0x1f5
    shr ecx, 8
    mov al, cl ;起始扇区编号高8位
    out dx, al
    
    inc dx ;0x1f6
    shr ecx, 8
    and cl, 0b1111 ;将高四位设置为0
    
    mov al, 0b1110_0000 ;主盘，LBA模式
    or al, cl
    out dx, al

    inc dx ;0x1f7
    mov al, 0x20 ;读硬盘
    out dx, al

    xor ecx, ecx
    mov cl, bl ;得到读写扇区数量

    .read:
        push cx ;保存cx
        call .waits ;等待数据准备完毕
        call .reads ;读取一个扇区
        pop cx
        loop .read

    ret

    .waits:
        mov dx, 0x1f7
        .check:
            in al, dx
            jmp $+2 ;直接跳转下一行
            jmp $+2 ;一点点延迟
            jmp $+2
            and al, 0b1000_1000
            cmp al, 0b0000_1000
            jnz .check
        ret

    .reads:
        mov dx, 0x1f0
        mov cx, 256
        .readw:
            in ax, dx
            jmp $+2 ;直接跳转下一行
            jmp $+2 ;一点点延迟
            jmp $+2
            mov [edi], ax
            add edi, 2
            loop .readw
        ret 

code_selector equ (1 << 3)
date_selector equ (2 << 3)
memory_base equ 0 ;内存开始位置
memory_limit equ (1024 * 1024) - 1;内存界限
gdt_ptr:
    dw (gdt_ends - gdt_base) - 1
    dd gdt_base
gdt_base:
    dd 0, 0 ;gdt开始位置
gdt_code:
    dw memory_limit & 0xffff ;段界限0-15位
    dw memory_base & 0xffff ;基地址0-15位
    db (memory_base >> 16) & 0xff ;基地址16-23位
    db (0b_1_00_1_1_0_1_0) ; 存在 -dpl 0 -代码或数据 -代码 -非依存 -可读 -没有访问过
    db 0b1_1_0_0_0000 | (memory_limit >> 16) & 0xf; 4k -32位 -不是64位 -段界限16-19位
    db (memory_base >> 24) & 0xff ;基地址24-31位
gdt_data:
    dw memory_limit & 0xffff ;段界限0-15位
    dw memory_base & 0xffff ;基地址0-15位
    db (memory_base >> 16) & 0xff ;基地址16-23位
    db (0b_1_00_1_0_0_1_0) ; 存在 -dpl 0 -代码或数据 -数据 -向上拓展 -可写 -没有访问过
    db 0b1_1_0_0_0000 | (memory_limit >> 16) & 0xf; 4k -32位 -不是64位 -段界限16-19位
    db (memory_base >> 24) & 0xff ;基地址24-31位
gdt_ends:

loading:
    db "Loading Myos...", 10, 13, 0 ;\n\r\0

detecting:
    db "Detecting Memory Success...", 10, 13, 0 ;\n\r\0

ards_count:
    dd 0

ards_buffer: 
