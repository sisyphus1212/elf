
DEFAULT    ?= n
EXEC_SHLIB ?= y

ifeq ($(DEFAULT), y)
  # The generated position independent executables can not be shared loaded in Ubuntu 20.04 now.
  CFLAGS := -m32 -pie -fpie -rdynamic
else
  CFLAGS := -m32 -shared -fpic
  ifeq ($(EXEC_SHLIB), y)
    CFLAGS += -DEXEC_SHLIB
  endif
endif

OBJS := libhello.so dlopen main

all: libhello.so main dlopen

libhello.so: hello.c
	gcc $(CFLAGS) -o $@ $<
	./$@

dlopen: dlopen.c libhello.so
	gcc -m32 -rdynamic -o $@ $< -ldl
	./$@

main: main.c libhello.so
	gcc -m32 -o $@ $< -L./ -lhello
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./ ./$@

FORCE:

clean:
	rm -rf $(OBJS)
