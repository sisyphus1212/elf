
SRCS   = $(wildcard *.asm) $(wildcard *.s)
EXEC   = $(basename $(SRCS))

all: $(EXEC)

%: %.asm FORCE
	nasm -f bin $< -o $@
	@echo "Running $@"
	@chmod +x $@
	@./$@ ; echo "Return value: $$?"

%: %.s FORCE
	as --32 -o $@.o $<
	ld -melf_i386 --oformat=binary -o $@ $@.o
	@echo "Running $@"
	@PATH=./:$(PATH) $@ 0 0 0 0 0 0 0 0
	@echo

FORCE:

clean:
	rm -rf $(EXEC) *.o
