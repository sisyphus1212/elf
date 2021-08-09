
all: run-bin

dep:
	@[ ! -d /usr/include/asm ] && sudo ln -sf /usr/include/asm-generic/ /usr/include/asm || true

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: malloc-pic.c hello.bin dep
	gcc -m32 -o $@ $<
	./$@ hello.bin

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
