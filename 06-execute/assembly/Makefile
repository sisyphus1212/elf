
TOP_DIR = $(CURDIR)
ASMS = $(wildcard *.s)
OBJS = $(ASMS:.s=)
STRIP ?=y

CROSS_COMPILE ?=

AS = $(CROSS_COMPILE)as --32 -g
LD = $(CROSS_COMPILE)ld -m elf_i386

LD_SCRIPT ?= y
ifeq ($(LD_SCRIPT),y)
  LD += -Tld.script
endif

ifeq ($(filter nihao, $(MAKECMDGOALS)),nihao)
  LD += --oformat=binary
  STRIP := n
endif

all: $(OBJS) force

%: %.s force
	$(AS) -o $@.o $<
	$(LD) -o $@ $@.o
ifeq ($(STRIP), y)
	wc -c $@
	strip -s $@
	wc -c $@
	dd if=$@ of=$@.strip bs=1 count=$$((0x$$(readelf -S $@ | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
	mv $@.strip $@
	chmod +x $@
	wc -c $@
endif
	PATH=$(PATH):./ $@ hello 0 0 0; echo ; echo $$?

force:

clean: $(OBJS)
	rm -rf *.o $^
