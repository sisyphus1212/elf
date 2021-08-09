# Must install qemu-user at first
SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
CFLAGS := -m32

ALL = $(EXEC)

all: $(ALL)

%: %.c FORCE
	gcc -o $@ $< $(CFLAGS)
	qemu-i386 ./$@

FORCE:

clean:
	rm -rf $(ALL)
