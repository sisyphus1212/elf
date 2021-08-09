
SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
ARCH   = x86 arm ppc

CC    ?= gcc
RUN   ?=

CFLAGS ?= -m32

all: $(EXEC)

compare: $(ARCH)

x86:
	@echo
	@echo "    $@:"
	@echo
	@make -s

arm:
	@echo
	@echo "    $@:"
	@echo
	@make -s CC=arm-linux-gnueabi-gcc \
		RUN="qemu-arm -L /usr/arm-linux-gnueabi/ " \
		CFLAGS=-Wl,--dynamic-linker=/usr/arm-linux-gnueabi/lib/ld-linux.so.3

ppc:
	@echo
	@echo "    $@:"
	@echo
	@make -s CC=powerpc-linux-gnu-gcc \
		RUN="qemu-ppc -L /usr/powerpc-linux-gnu/ " \
		CFLAGS="-static -Wl,--dynamic-linker=/usr/powerpc-linux-gnu/lib/ld-2.31.so.1"

%:%.c FORCE
	$(CC) $(CFLAGS) -o $@ $<
	$(RUN) ./$@

FORCE:

clean:
	rm -rf $(EXEC)
