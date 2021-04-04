GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARASM = -melf_i386

object = loader.o kernel.o

%.o : %.cpp
	g++ ${GCCPARAMS} -c -o $@ $<

%.o : %.s
	as ${ASPARAMS} -o $@ $<

mykernel.bin : linker.ld ${object}
	ld $(LDPARASM) -T $< -o $@ ${object}


