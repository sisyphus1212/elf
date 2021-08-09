OBJ  = hello.o
EXEC = hello
LOAD_ADDR := 0x8060000

all: run-bin

hello: hello.c FORCE
	gcc -m32 -pie -fpie -nostdlib -o hello hello.c -e mymain -lc
	./$@

run-bin: mmap-elf.c hello
	gcc -g -m32 -o $@ $<
	#./$@ hello

FORCE:

clean:
	rm -rf hello hello.o run-bin.o run-bin
