OBJ  = hello.o
EXEC = hello
LOAD_ADDR := 0x8060000

all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o
	#ld -melf_i386 -o $@ hello.o -Ttext=$(LOAD_ADDR) -Tld.script
	./$@

run-bin: mmap-elf.c hello
	gcc -g -m32 -o $@ $<
	./$@ hello

FORCE:

clean:
	rm -rf hello hello.o run-bin.o run-bin
