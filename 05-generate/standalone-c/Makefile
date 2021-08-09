
CC      = gcc
CUSTOM ?= y
LD_SCRIPT ?=y
NORMAL    ?=y
FORCE     := force

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
endif

ifeq ($(DEBUG),y)
  DEBUG_FLAGS += -g
endif
ifneq ($(STATIC_DETECTOR),n)
  CFLAGS+= -Wall -Werror
endif
ifneq ($(STD),)
  CFLAGS+= -std=$(STD)
endif

CC    += $(CFLAGS)

ifneq ($(CUSTOM), y)
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
  CC1  := $(shell ls /usr/lib/gcc/x86_64-linux-gnu/*/cc1 | tail -1)
  AS   := as
  LD   := ld

  ARCH   ?= i686
  PFLAGS += -DCUSTOM -E -imultilib 32 -m32 -march=$(ARCH)

  CFLAGS += -fpreprocessed -m32 -march=$(ARCH) >/dev/null 2>&1
  AFLAGS := --32 $(DEBUG_FLAGS)

  LIB32_GCC := $(shell ls -d /usr/lib/gcc/x86_64-linux-gnu/*/32 | tail -1)
  LIB32_C   := /usr/lib32
  LFLAGS    := -m elf_i386 --dynamic-linker /lib/ld-linux.so.2
endif

ifeq ($(LD_SCRIPT),y)
  LFLAGS   += -Tld.script
endif

Q      ?= $(if $(V),,@)

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
OBJS   = $(SRCS:.c=.o)
ASMS   = $(SRCS:.c=.s)
PRES   = $(SRCS:.c=.i)

ifneq ($(DEBUG),y)
  STRIP_OBJ := $(EXEC).strip
endif

ALL   := $(PRES) $(ASMS) $(OBJS) $(EXEC) $(STRIP_OBJ)
ifeq ($(NORMAL),y)
    ALL := normal $(ALL)
else
    ALL := $(ASMS) $(OBJS) $(EXEC) $(STRIP_OBJ)
endif

all: $(ALL) $(FORCE)
	-git checkout -- ld.script

%.nostart: %.c
	gcc -m32 -DCUSTOM -nostartfiles -o $@ $<
	./$@

normal: $(FORCE)
	cp ld.script.normal ld.script

ifeq ($(NORMAL),y)
%.i: %.c $(FORCE)
	$(CPP) $(PFLAGS) -o $@ $<

%.s: %.i $(FORCE)
	$(CC1) $(CFLAGS) -o $@ $<
else
%.s: %.c $(FORCE)
	cp hello.s.minimal hello.s
	git checkout -- ld.script
endif

%.o: %.s $(FORCE)
	$(AS) $(AFLAGS) -o $@ $<

%: %.o $(FORCE)
	$(LD) $(LFLAGS) $(DEBUG_FLAGS) -o $@ $< -lc

%.strip: % $(FORCE)
	size $<
	wc -c $<
	strip $<
	wc -c $<
	strip -R .eh_frame -R .note.ABI-tag -R .hash -R .comment -R .gnu.version $<
	wc -c $<
	readelf -l $<
	echo
	readelf -S $<
	dd if=$< of=$@ bs=1 count=$$((0x$$(readelf -S $< | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
	chmod +x $@
	wc -c $@
ifeq ($(LD_SCRIPT),y)
	/lib/ld-linux.so.2 ./$@
else
	./$@
endif

force:

clean:
	rm -f $(ALL) core *.i *.o hello.nostart*

distclean: clean
	rm -f *.s
