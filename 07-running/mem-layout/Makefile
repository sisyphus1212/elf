
CC    ?= gcc
CFLAGS+= -m32 -g -Tld.script

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

all: $(EXEC) force

%: %.c force
	$(CC) $(CFLAGS) -o $@ $<
	./$@

force:

clean:
	rm -rf $(EXEC)
