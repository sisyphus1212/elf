
CC    ?= gcc

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

all: $(EXEC)

%: %.c
	$(CC) -o $@ $<
	./$@

clean:
	rm -rf $(EXEC)
