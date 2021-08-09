
SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

CFLAGS = -m32 -g

ifeq ($(PACKED),y)
  CFLAGS += -DPACKED
endif

ifeq ($(PADDED),y)
  CFLAGS += -DPADDED
endif

all: $(EXEC)

pahole:
	@which pahole >/dev/null 2>&1 || (sudo apt-get update -y && sudo apt-get install -y dwarves || true)

list: pahole
	@echo "Default:"
	@echo
	make -s
	pahole -C test test
	@echo
	@echo "Packed:"
	@echo
	make -s PACKED=y
	pahole -C test test
	@echo
	@echo "Padded:"
	@echo
	make -s PADDED=y
	pahole -C test test
	@echo

%:%.c FORCE
	gcc $(CFLAGS) -o $@ $<
	./$@

cmake:
	@which cmake >/dev/null 2>&1 || (sudo apt-get update -y && sudo apt-get install -y cmake || true)

complex: cmake
	mkdir -p build && cd build && cmake ../ && make && ./mem_align

FORCE:

clean:
	rm -rf $(EXEC)
