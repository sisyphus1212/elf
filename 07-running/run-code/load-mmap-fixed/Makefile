
LOAD_ADDR := 0x8046000

all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o -Ttext=$(LOAD_ADDR)
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: mmap-fixed.c hello.bin
	gcc -m32 -o $@ $<
	./$@ hello.bin 0 $(LOAD_ADDR)

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
