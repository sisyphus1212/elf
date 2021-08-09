
STD   ?=
CC     = gcc


ifneq ($(DEFAULT),y)
  CFLAGS = -fno-stack-protector
  CFLAGS+= -fomit-frame-pointer
  CFLAGS+= -fno-asynchronous-unwind-tables
  CFLAGS+= -fno-pie -no-pie
  CFLAGS+= -m32
endif

ifneq ($(CALL),)
  ifneq ($(filter $(CALL), cdecl fastcall), $(CALL))
    $(warning "$(CALL) may be not supported")
  endif
  CFLAGS += -DFUNC_CALL_ATTR=$(CALL)
endif

ifeq ($(STD_ERROR),y)
  CFLAGS += -DSTD_ERROR
endif

ifeq ($(OTHER_ERROR),y)
  CFLAGS += -DOTHER_ERROR
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
  CFLAGS+= -Wall -Wextra -Werror -Wfatal-errors

  # reject all programs that use forbidden extensions
  CFLAGS+= -pedantic -pedantic-errors
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

ALL   := $(EXEC) $(OBJS) $(ASMS) $(PRES) core

all: $(EXEC) $(FORCE)

compare:
	@make --no-print-directory clean
	make --no-print-directory func-call CALL=cdecl
	@make --no-print-directory clean
	make --no-print-directory func-call CALL=fastcall

std:
	@for std in c89 c90 c99 c11 c17 gnu89 gnu99 gnu11 gnu17; do \
		echo $$std ; \
		make -s clean && make -s STD=$$std; \
		echo; \
	done;	\
	echo default;	\
	make -s;	\
	echo

%: %.c $(FORCE)
	$(CC) $(DEBUG_CFLAGS) -o $@ $<
	@PATH=$(CURDIR):$(PATH) $@
ifeq  ($(filter func-call, $(MAKECMDGOALS)), func-call)
	@objdump -d -j .text $@ | grep -B8 -A10 "call.*func"
	@objdump -d -j .text $@ | grep -A16 "func>:"
endif

%.o: %.c $(FORCE)
	$(CC) -c -o $@ $<

%.s: %.c $(FORCE)
	$(CC) -S -o $@ $<

%.i: %.c $(FORCE)
	$(CC) -E -o $@ $<

force:

clean:
	rm -f $(ALL)
