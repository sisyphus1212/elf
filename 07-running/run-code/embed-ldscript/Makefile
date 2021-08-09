
all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o -Ttext=0x8060000
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: run-bin.c hello.bin
	gcc -m32 -c -o run-bin.o $<
	gcc -m32 -o $@ run-bin.o -Tld.script
	./$@

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
