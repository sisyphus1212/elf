
all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: run-bin.c hello.bin
	gcc -m32 -o $@ $<
	./$@

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
