BUILD:=../build
SRC:=.

ENTRYPOINT:=0x10000 #入口地址

CFLAGS:= -m32 # 32位程序
CFLAGS+= -fno-builtin # 不需要gcc内置函数
CFLAGS+= -nostdinc # 不需要标准头文件
CFLAGS+= -fno-pic # 不需要位置无关代码 position independent code
CFLAGS+= -fno-pie # 不需要位置无关可执行程序 position independent executable
CFLAGS+= -nostdlib # 不需要标准库
CFLAGS+= -fno-stack-protector # 不需要栈保护
CFLAGS:= $(strip $(CFLAGS)) 

DEBUG:= -g

INCLUDE:= -I$(SRC)/include

$(BUILD)/boot/%.bin: $(SRC)/boot/%.asm
	$(shell mkdir -p $(dir $@))
	nasm -f bin $< -o $@

$(BUILD)/kernel/%.o: $(SRC)/kernel/%.asm
	$(shell mkdir -p $(dir $@))
	nasm -f elf32 $(DEBUG) $< -o $@

$(BUILD)/kernel/%.o: $(SRC)/kernel/%.c
	$(shell mkdir -p $(dir $@))
	gcc $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

$(BUILD)/lib/%.o: $(SRC)/lib/%.c
	$(shell mkdir -p $(dir $@))
	gcc $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

$(BUILD)/kernel.bin: $(BUILD)/kernel/start.o \
					 $(BUILD)/kernel/main.o \
					$(BUILD)/kernel/io.o \
					$(BUILD)/kernel/console.o \
					$(BUILD)/kernel/printk.o \
					$(BUILD)/kernel/assert.o \
					$(BUILD)/kernel/debug.o \
					$(BUILD)/kernel/global.o \
					$(BUILD)/kernel/task.o \
					$(BUILD)/kernel/schedule.o \
					$(BUILD)/kernel/interrupt.o \
					$(BUILD)/kernel/handler.o \
					$(BUILD)/kernel/clock.o \
					$(BUILD)/kernel/time.o \
					$(BUILD)/kernel/rtc.o \
					$(BUILD)/kernel/memory.o \
					$(BUILD)/lib/stdlib.o \
					$(BUILD)/lib/vsprintf.o \
					$(BUILD)/lib/string.o
	$(shell mkdir -p $(dir $@))
	ld -m elf_i386 -static $^ -o $@ -Ttext $(ENTRYPOINT)

# .bss展开，避免需要动态解析增加汇编程序复杂度
$(BUILD)/system.bin: $(BUILD)/kernel.bin
	objcopy -O binary $< $@     

$(BUILD)/system.map: $(BUILD)/kernel.bin
	nm $< | sort > $@

$(BUILD)/master.img: $(BUILD)/boot/boot.bin \
			$(BUILD)/boot/loader.bin \
			$(BUILD)/system.bin \
			$(BUILD)/system.map
# 创建一个 16M 的硬盘镜像
	yes | bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $@
# 将 boot.bin 写入主引导扇区
	dd if=$(BUILD)/boot/boot.bin of=$@ bs=512 count=1 conv=notrunc
# 将 loader.bin 写入硬盘
	dd if=$(BUILD)/boot/loader.bin of=$@ bs=512 count=4 seek=2 conv=notrunc
# 测试 system.bin 小于 100k，否则需要修改下面的 count
	test -n "$$(find $(BUILD)/system.bin -size -100k)"
# 将 system.bin 写入硬盘
	dd if=$(BUILD)/system.bin of=$@ bs=512 count=200 seek=10 conv=notrunc

test: $(BUILD)/kernel.bin

QEMU:= qemu-system-i386 \
	-m 32M \
	-boot c \
	-drive file=$(BUILD)/master.img,if=ide,index=0,media=disk,format=raw \
	-audiodev pa,id=hda \
	-machine pcspk-audiodev=hda \
	-rtc base=localtime \

.PHONY: qemu
qemu: $(BUILD)/master.img
	$(QEMU)

.PHONY: qemug
qemug: $(BUILD)/master.img
	$(QEMU) -s -S

.PHONY: clean
clean:
	rm -rf $(BUILD)

