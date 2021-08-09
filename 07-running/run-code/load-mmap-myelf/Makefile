OBJ  = hello.o
EXEC = hello
LOAD_ADDR := 0x8060000

all: run-bin

hello: hello.s FORCE
	as --32 -o hello.o $<
	ld -melf_i386 -o $@ hello.o -Ttext=$(LOAD_ADDR) -Tld.script
	./$@

hello.bin: hello FORCE
	objcopy -O binary $< $@

hello.myelf: hello.bin
	bash -c "echo -en '\x7FMYE' > $@"
	bash -c "echo -en $$(readelf -r $(OBJ)  | grep .rodata | tail -1 | cut -d' ' -f1 \
		| sed -e 's/\([0-9a-f]\{2,2\}\)/\\\\x\1/g') >> $@"
	bash -c "echo -en $$(readelf -S $(EXEC) | grep .text | tr -s ' ' | sed -e 's/.*\.//g' | cut -d' ' -f5 \
		| xargs -i echo '00000000{}' | sed -e 's/0*\([0-9a-f]\{8,8\}\)/\1/g' \
		| sed -e 's/\([0-9a-f]\{2,2\}\)/\\\\x\1/g') >> $@"
	cat $< >> $@
	chmod a+x $@

run-bin: mmap-myelf.c hello.myelf
	gcc -g -m32 -o $@ $<
	sudo ./$@ hello.myelf

FORCE:

clean:
	rm -rf hello hello.bin hello.myelf hello.o run-bin.o run-bin
