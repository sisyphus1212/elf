
CC      = gcc
CUSTOM ?= y
INIT_FINI ?=y

ifeq ($(INIT_FINI), y)
  PFLAGS := -DINIT_FINI -DAT_EXIT
endif

ifneq ($(DEFAULT),y)
  #CFLAGS = -fno-stack-protector
  #CFLAGS+= -fomit-frame-pointer
  CFLAGS+= -fno-asynchronous-unwind-tables
  #CFLAGS+= -fno-pie -no-pie
  #CFLAGS+= -m32
endif

ifeq ($(SEGFAULT_TEST),y)
  CFLAGS += -DSEGFAULT_TEST
  STATIC_DETECTOR ?= n
  FORCE := force
endif

ifeq ($(DEBUG),y)
  DEBUG_CFLAGS += -g
  FORCE := force
endif
ifneq ($(STATIC_DETECTOR),n)
  CFLAGS+= -Wall -Werror
else
  FORCE := force
endif
ifneq ($(STD),)
  CFLAGS+= -std=$(STD)
  FORCE := force
endif

CC    += $(CFLAGS)

ifneq ($(CUSTOM), y)
  CC   += -m32
  CPP  := $(CC)
  CC1  := $(CC)
  AS   := $(CC)
  LD   := $(CC)

  PFLAGS += -E
  CFLAGS += -S
  AFLAGS := -c
  LFLAGS :=

else

  CPP  := cpp
  #CPP  := /usr/lib/gcc/x86_64-linux-gnu/8/cc1
  CC1  := $(shell ls /usr/lib/gcc/x86_64-linux-gnu/*/cc1 | tail -1)
  AS   := as
  LD   := ld
  #LD   := /usr/lib/gcc/x86_64-linux-gnu/8/collect2

  ARCH   ?= i686
  PFLAGS += -E -imultilib 32 -m32 -march=$(ARCH)
  #PFLAGS := -E -imultilib 32 -m32 -mtune=generic -march=i686
  #PFLAGS := -E -quiet -imultilib 32 -imultiarch i386-linux-gnu -m32 -mtune=generic -march=i686 -fstack-protector-strong -Wformat -Wformat-security

  CFLAGS += -fpreprocessed -m32 -march=$(ARCH) -quiet #-dumpbase hello.i -auxbase hello
  #CFLAGS += -fpreprocessed -m32 -march=$(ARCH) >/dev/null 2>&1 #-dumpbase hello.i -auxbase hello
  #CFLAGS := -fpreprocessed -quiet -m32 -mtune=generic -march=i686 -version >/dev/null 2>&1 #-dumpbase hello.i -auxbase hello
  #CFLAGS := -fpreprocessed -quiet -m32 -mtune=generic -march=i686 -version -fstack-protector-strong -Wformat -Wformat-security >/dev/null 2>&1 #-dumpbase hello.i -auxbase hello
  AFLAGS := --32
  #LFLAGS := -plugin /usr/lib/gcc/x86_64-linux-gnu/8/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/8/lto-wrapper -plugin-opt=-fresolution=/tmp/ccX8yX0t.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_i386 --hash-style=gnu --as-needed -dynamic-linker /lib/ld-linux.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/8/../../../i386-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/8/../../../i386-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/8/32/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/8/32 -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../i386-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../../lib32 -L/lib/i386-linux-gnu -L/lib/../lib32 -L/usr/lib/i386-linux-gnu -L/usr/lib/../lib32 -L/usr/lib/gcc/x86_64-linux-gnu/8 -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../i386-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/8/../../.. -L/lib/i386-linux-gnu -L/usr/lib/i386-linux-gnu -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state /usr/lib/gcc/x86_64-linux-gnu/8/32/crtend.o /usr/lib/gcc/x86_64-linux-gnu/8/../../../i386-linux-gnu/crtn.o

  LIB32_GCC := $(shell ls -d /usr/lib/gcc/x86_64-linux-gnu/*/32 | tail -1)
  LIB32_C   := /usr/lib32
  # atexit requires __dso_handle defined in crtbegin.o
  LFLAGS    := -m elf_i386 --dynamic-linker /lib/ld-linux.so.2 $(LIB32_C)/crt1.o $(LIB32_C)/crti.o $(LIB32_GCC)/crtbegin.o $(LIB32_GCC)/crtend.o -L$(LIB32_GCC) $(LIB32_C)/crtn.o
  #LFLAGS    := --build-id --eh-frame-hdr -m elf_i386 --hash-style=gnu --dynamic-linker /lib/ld-linux.so.2 -z relro $(LIB32_C)/crt1.o $(LIB32_C)/crti.o $(LIB32_GCC)/crtbegin.o -lc $(LIB32_GCC)/crtend.o $(LIB32_C)/crtn.o
  #LFLAGS    := --build-id --eh-frame-hdr -m elf_i386 --hash-style=gnu -dynamic-linker /lib/ld-linux.so.2 -z relro $(LIB32_C)/crt1.o $(LIB32_C)/crti.o $(LIB32_GCC)/crtbegin.o -L$(LIB32_GCC) -lgcc_s -lgcc $(LIB32_C) -lc $(LIB32_GCC)/crtend.o $(LIB32_C)/crtn.o
endif


Q      ?= $(if $(V),,@)

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
STRIPS = $(SRCS:.c=.strip)
OBJS   = $(SRCS:.c=.o)
ASMS   = $(SRCS:.c=.s)
PRES   = $(SRCS:.c=.i)

ALL   := $(PRES) $(ASMS) $(OBJS) $(EXEC) $(STRIPS)

all: $(ALL) $(FORCE)

core:

%.i: %.c $(FORCE)
	$(CPP) $(PFLAGS) -o $@ $<

%.s: %.i $(FORCE)
	$(CC1) $(CFLAGS) -o $@ $<

%.o: %.s $(FORCE)
	$(AS) $(AFLAGS) -o $@ $<

%: %.o $(FORCE)
	$(LD) $(LFLAGS) $(DEBUG_CFLAGS) -o $@ $< -lc

%.strip: % $(FORCE)
	size $<
	wc -c $<
	strip $<
	wc -c $<
	strip -R .eh_frame -R .note.ABI-tag -R .hash -R .comment -R .gnu.version $<
	wc -c $<
	readelf -S $<
	dd if=$< of=$@ bs=1 count=$$((0x$$(readelf -S $< | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
	chmod +x $@
	wc -c $@
	./$@

force:

clean:
	rm -f $(ALL)
