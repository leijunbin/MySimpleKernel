GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARASM = -melf_i386

object = loader.o kernel.o gdt.o

%.o : %.cpp
	g++ ${GCCPARAMS} -c -o $@ $<

%.o : %.s
	as ${ASPARAMS} -o $@ $<

mykernel.bin : linker.ld ${object}
	ld $(LDPARASM) -T $< -o $@ ${object}

mykernel.iso : mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub//grub.cfg
	echo '' >> iso/boot/grub//grub.cfg
	echo 'menuentry "my os" {' >> iso/boot/grub//grub.cfg
	echo '  multiboot /boot/mykernel.bin' >> iso/boot/grub//grub.cfg
	echo '  boot' >> iso/boot/grub//grub.cfg
	echo '}' >> iso/boot/grub//grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run : mykernel.iso
	(killall VirtualBoxVM && sleep 1) || true
	virtualboxvm --startvm "MyOs" &

