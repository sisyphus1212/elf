
CC    ?= gcc
CFLAGS+= -m32 -g

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

all: $(EXEC)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
	./$@

clean:
	rm -rf $(EXEC)
