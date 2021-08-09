
CC     = gcc

ifneq ($(DEFAULT),y)
  CFLAGS+= -m32
endif

# Default Section
ifeq ($(filter disasm, $(MAKECMDGOALS)), disasm)
  S     ?= .text
else
  ifeq ($(filter strip-section, $(MAKECMDGOALS)), strip-section)
    S   ?= .comment
  else
    S   ?= .strtab
  endif
endif

CC    += $(CFLAGS)

Q      ?= $(if $(V),,@)

SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
OBJS   = $(SRCS:.c=.o)
ASMS   = $(SRCS:.c=.s)
PRES   = $(SRCS:.c=.i)

ifeq ($(filter strip-sections, $(MAKECMDGOALS)), strip-sections)
  DROP_SECTIONS?= .note.ABI-tag .note.gnu.build-id .gnu.hash .comment .eh_frame .eh_frame_hdr
  STRIP_FLAGS  := $(addprefix -R,$(DROP_SECTIONS))
endif

ifeq ($(filter $(MAKECMDGOALS), null-gnu-segments null-pht-paddrs), $(MAKECMDGOALS))
  SEGMENTS_TOTAL = $(shell readelf -h hello | grep "Number of program headers" | cut -d ':' -f2 | tr -d ' ')
  GNU_SEGMENTS_TOTAL = $(shell readelf -l hello | egrep "GNU|NOTE" | wc -l)
endif

ALL   := $(PRES) $(ASMS) $(OBJS) $(EXEC)

all: $(ALL) FORCE
	$(Q)PATH=$(CURDIR):$(PATH) $(EXEC)

%: %.c FORCE
	$(CC) $(DEBUG_CFLAGS) -o $@ $<

%.o: %.c FORCE
	$(CC) -c -o $@ $<

%.s: %.c FORCE
	$(CC) -S -o $@ $<

%.i: %.c FORCE
	$(CC) -E -o $@ $<

size: $(EXEC)
	size $< 

eh: $(EXEC)
	readelf -h $<

pht: $(EXEC)
	readelf -l $<

sht: $(EXEC)
	readelf -S $<

symtab: $(EXEC)
	readelf -s $<

strtab: $(EXEC)
	readelf -s $<

dynsym: $(EXEC)
	readelf --dyn-sym $<

dynamic: $(EXEC)
	readelf -d $<

note: $(EXEC)
	readelf -n $<

version: $(EXEC)
	readelf -V $<

eh_frame: $(EXEC)
	eu-readelf -e $<

relocs: $(EXEC)
	readelf -r $<

sort-sections: $(EXEC)
	readelf -S $< | sed -ne '/ \[/s/^ [[ ]*//p' | \
	grep -v Name | tr -s ' ' | cut -d ' ' -f2,6 | \
	awk --non-decimal-data '{ printf("%-18 s %-5d\n", $$1, "0x" $$2);}' | sort -g -k2 -r

disasm: $(EXEC)
	objdump -d -j $S $<

hex: $(EXEC)
	readelf -x $S $<

string: $(EXEC)
	readelf -p $S $<

null-gnu-segments: $(EXEC)
	dd if=/dev/zero of=$< seek=$$((52+32*($(SEGMENTS_TOTAL)-$(GNU_SEGMENTS_TOTAL)))) count=$$((32*$(GNU_SEGMENTS_TOTAL))) bs=1 conv=notrunc
	readelf -l $<

null-pht-paddrs: $(EXEC)
	$(foreach segment, $(shell seq 1 $(SEGMENTS_TOTAL)), \
	echo;dd if=/dev/zero of=hello bs=1 seek=$$((52+($(segment)-1)*32+3*4)) count=4 conv=notrunc;)
	readelf -l $<

strip-section: $(EXEC)
	wc -c $<
	objcopy -R $S $<
	wc -c $<

strip: $(EXEC)
	wc -c $<
	strip $<
	wc -c $<

strip-sections: $(EXEC)
	wc -c $<
	strip $(STRIP_FLAGS) $<
	wc -c $<

strip-nonexec: $(EXEC)
	wc -c $<
	dd if=$< of=$<.strip bs=1 count=$$((0x$$(readelf -S $< | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
	mv $<.strip $<
	chmod a+x $<
	wc -c $<

strip-all: $(EXEC)
	make strip-sections strip-nonexec

FORCE:

clean:
	rm -f $(ALL)
