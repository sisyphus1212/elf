OBJ  = hello.o
EXEC = hello
LOAD_ADDR := 0x8060000

all: run-bin

# It requies linux-libc-dev-i386-cross
dep:
	@[ ! -d /usr/include/asm ] && sudo ln -sf /usr/include/asm-generic/ /usr/include/asm || true

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o -Ttext=$(LOAD_ADDR) -Tld.script
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

run-bin: malloc-auto.c hello.bin dep
	gcc -m32 -o $@ $<
	./$@ hello.bin \
		$$((0x$$(readelf -r $(OBJ)  | grep .rodata | tail -1 | cut -d' ' -f1))) \
		$$((0x$$(readelf -S $(EXEC) | grep .text | tr -s ' ' | sed -e "s/.*\.//g" | cut -d' ' -f5)))

FORCE:

clean:
	rm -rf hello hello.bin hello.o run-bin.o run-bin
