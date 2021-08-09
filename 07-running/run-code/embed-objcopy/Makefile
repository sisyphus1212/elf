
all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o -Ttext=0x8060000
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: run-bin.c hello.bin
	gcc -m32 -c -o run-bin.o $<
	objcopy --add-section .bin=hello.bin --set-section-flags .bin=contents,alloc,load,readonly,code --add-symbol bin_entry=.bin:0,global run-bin.o
	gcc -m32 -Wl,--section-start=.bin=$(shell readelf -l hello | grep "^Entry point" | cut -d ' ' -f3) -o $@ run-bin.o
	./$@

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
