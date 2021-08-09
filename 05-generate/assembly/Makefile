
TOP_DIR = $(CURDIR)
ASMS = $(wildcard *.s)
OBJS = $(ASMS:.s=)
STRIP ?=y

CROSS_COMPILE ?=

AS = $(CROSS_COMPILE)as --32
LD = $(CROSS_COMPILE)ld -m elf_i386

ifeq ($(LD_SCRIPT),y)
  LD += -Tld.script
endif

all: $(OBJS)

%.nostdlib: %.s
	gcc -nostdlib -m32 -o $@ $<
ifeq ($(STRIP), y)
	wc -c $@
	strip -s $@
	wc -c $@
	dd if=$@ of=$@.strip bs=1 count=$$((0x$$(readelf -S $@ | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
	mv $@.strip $@
	chmod +x $@
	wc -c $@
endif
	./$@ ; echo $$?


%: %.s
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
	./$@ ; echo $$?

clean: $(OBJS)
	rm -rf *.o $^ *.nostdlib
