
CC    ?= gcc
CFLAGS+= -m32 -g

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

all: run force
	
run: $(EXEC)
	./$(EXEC)

%: %.c force
	$(CC) $(CFLAGS) -o $@ $<

force:

clean:
	rm -rf $(EXEC)
