
CC     := $(CROSS_COMPILE)gcc

ifneq ($(DEFAULT),y)
  CFLAGS+= -fno-stack-protector
  CFLAGS+= -fomit-frame-pointer
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

Q      ?= $(if $(V),,@)

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
OBJS   = $(SRCS:.c=.o)
ASMS   = $(SRCS:.c=.s)
PRES   = $(SRCS:.c=.i)

ALL   :=  $(PRES) $(ASMS) $(OBJS)  $(EXEC)

all: $(ALL) force
ifeq ($(CROSS_COMPILE),)
	$(Q)PATH=$(CURDIR):$(PATH) $(EXEC)
endif

%: %.c $(FORCE)
	$(CC) $(DEBUG_CFLAGS) -o $@ $<

%.o: %.c $(FORCE)
	$(CC) -c -o $@ $<

%.s: %.c $(FORCE)
	$(CC) -S -o $@ $<

%.i: %.c $(FORCE)
	$(CC) -E -o $@ $<

arm:
	make CROSS_COMPILE=arm-linux-gnueabi-
	qemu-arm-static -L /usr/arm-linux-gnueabi/ ./tinysh

arm-static:
	make CROSS_COMPILE=arm-linux-gnueabi- CFLAGS=-static
	qemu-arm-static -L /usr/arm-linux-gnueabi/ ./tinysh

force:

clean:
	rm -f $(ALL)
