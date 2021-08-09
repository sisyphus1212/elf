SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

ALL = $(EXEC)

all: $(ALL)

%: %.c FORCE
	gcc -m32 -o $@ $<
	./$@

FORCE:

clean:
	rm -rf $(ALL)
