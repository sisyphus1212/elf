
all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o -Tld.script
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: mmap-pic.c hello.bin
	gcc -m32 -o $@ $<
	./$@ hello.bin 0

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
