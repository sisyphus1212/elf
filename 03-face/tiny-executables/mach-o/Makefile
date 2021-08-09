
SRCS   = $(wildcard *.asm)
EXEC   = $(addsuffix .macho, $(basename $(SRCS)))

all: $(EXEC)

%.macho: %.asm
	yasm -f bin $< -o $@
	@echo "Require darling from https://github.com/darlinghq/darling"
	@#echo "Running $@ with darling"
	@#darling shell $@; echo "Return value: $$?"

clean:
	rm -rf $(EXEC)
