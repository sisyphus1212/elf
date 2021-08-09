
SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
CFLAGS+= -m32 -rdynamic -ldl

ALL = $(EXEC)

all: $(ALL)

%: %.c FORCE
	gcc -o $@ $< $(CFLAGS)
	./$@

FORCE:

clean:
	rm -rf $(ALL)
