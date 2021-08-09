
AFLAGS := --32
LFLAGS := -melf_i386 --oformat=binary

CFLAGS := -m32 -Wl,--oformat=binary -nostdlib -nostartfiles

run: hello
	@echo $@ $^
	@PATH=./:$(PATH) $^ 0 0 0 0
	@echo

hello.o: hello.s
	as $(AFLAGS) -o $@ $<

hello: hello.o
	ld $(LFLAGS) -o $@ $<

hello.gcc: hello.s
	gcc $(CFLAGS) -o $@ $<
	@echo run $@
	@PATH=$(PATH):./ $@ 0 0 0 0 0 0 0 0
	@echo

clean:
	rm -rf hello.gcc hello hello.o
