
CFLAGS := -m32 -shared -fpic -DEXEC_SHLIB
OBJS   := libhello.so

all: $(OBJS)

lib%.so: %.c FORCE
	gcc $(CFLAGS) -o $@ $<
	./$@

FORCE:

clean:
	rm -rf $(OBJS)
