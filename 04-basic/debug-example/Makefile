
CC     = gcc
FORCE := force

ifneq ($(DEFAULT),y)
  #CFLAGS = -fno-stack-protector
  #CFLAGS+= -fomit-frame-pointer
  #CFLAGS+= -fno-asynchronous-unwind-tables
  #CFLAGS+= -fno-pie -no-pie
  CFLAGS+= -m32
endif

ifeq ($(OVERFLOW_TEST),y)
  CFLAGS += -DOVERFLOW_TEST
  CFLAGS += -fstack-protector-all
  DEBUG_CFLAGS += -g
  STATIC_DETECTOR ?= n
endif

ifeq ($(SEGFAULT_TEST),y)
  CFLAGS += -DSEGFAULT_TEST
  DEBUG_CFLAGS += -g
  STATIC_DETECTOR ?= n
endif

ifeq ($(DEBUG),y)
  DEBUG_CFLAGS += -g
endif
ifneq ($(STATIC_DETECTOR),n)
  CFLAGS+= -Wall -Werror
endif
ifneq ($(STD),)
  CFLAGS+= -std=$(STD)
endif

CC    += $(CFLAGS)

Q      ?= $(if $(V),,@)

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
OBJS   = $(SRCS:.c=.o)
ASMS   = $(SRCS:.c=.s)
PRES   = $(SRCS:.c=.i)

ALL   := $(PRES) $(ASMS) $(OBJS) $(EXEC)

all: $(ALL) $(FORCE)

core: $(FORCE)
	$(Q)make -s STATIC_DETECTOR=n SEGFAULT_TEST=y $(EXEC)

%: %.c $(FORCE)
	$(CC) $(DEBUG_CFLAGS) -o $@ $<
	$(Q)PATH=$(CURDIR):$(PATH) $(EXEC)

%.o: %.c $(FORCE)
	$(CC) -c -o $@ $<

%.s: %.c $(FORCE)
	$(CC) -S -o $@ $<

%.i: %.c $(FORCE)
	$(CC) -E -o $@ $<

cscope:
	cscope -Rbkq

force:

clean:
	rm -f $(ALL) cscope.* core
