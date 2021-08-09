
SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))
OBJS   = $(EXEC) $(EXEC).o lib$(EXEC).a $(EXEC).froma lib$(EXEC).so $(EXEC).noc

SHARED_CFLAGS = -shared -fpic

ifeq ($(SHARED_EXEC_MANUAL),y)
  SHARED_CFLAGS += -DSHARED_EXEC_MANUAL -Wl,-e,main
  SHARED_EXEC   := 1
endif

# This not work in latest Ubuntu 20.04
ifeq ($(SHARED_EXEC_AUTO),y)
  SHARED_CFLAGS := -pie -Wl,-E
  SHARED_EXEC   := 1
endif

all: $(OBJS)

%.froma:lib%.a
	@echo
	@echo "[*] Building directly from static library"
	@echo
	gcc -m32 -o $@ $<
	./$@
	@echo

lib%.a:%.o FORCE
	@echo
	@echo "[*] Generating static library"
	@echo
	ar -r $@ $<
	@echo
	@echo "[*] Showing armap"
	@echo
	nm -s $@
	@echo

# Build an executable from no c if the dynamic have a main entry
%.noc:lib%.so
	@echo
	@echo "[*] Generating executable from no c and shared object with main entry"
	@echo
	gcc -m32 -o $@ -L./ -l$(EXEC)
	LD_LIBRARY_PATH=./ ./$@
	@echo

# IF compile from .o, .o must be compiled with -fpic too
lib%.so:%.c FORCE
	@echo
	@echo "[*] Generating shared objects"
	@echo
	gcc -m32 $(SHARED_CFLAGS) -o $@ $<
	@echo
	@echo "[*] Checking position independent code logic"
	@echo
	objdump -d -j .text $@ | head -9 | tail -3
	@echo
ifneq ($(SHARED_EXEC),)
	@echo "[*] Running shared objects"
	@echo
	./$@
	@echo
endif

%: %.c FORCE
	@echo
	@echo "[*] Generating executable"
	@echo
	gcc -m32 -o $@ $<
	@echo "[*] Lising used shared libraries"
	@echo
	ldd $@
	@echo
	@echo "[*] Checking symbols' address"
	@echo
	objdump -d $@ | grep -B1 "call.*puts"
	@echo
	@echo "[*] Stripping section header table and .shstrtab, .symtab, .strtab"
	@echo
	wc -c $@
	strip $@
	wc -c $@
	dd if=$@ of=$@.strip bs=1 count=$$((0x$$(readelf -S $@ | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
	wc -c $@
	mv $@.strip $@
	chmod a+x $@
	@echo
	@echo "[*] Running $@ without section header table"
	@echo
	sync
	./$@
	@echo

# The hello.c with .interpreter can not be compiled to .o at first
%.o: %.c FORCE
	@echo
	@echo "[*] Generating relocable"
	@echo
	gcc -m32 -c $<
	@echo
	@echo "[*] Checking program header"
	readelf -l $@
	@echo
	@echo "[*] Checking symbols' address"
	objdump -d -r $@ | grep -B1 R_
	@echo "[*] Clear the puts linking addr"
	@echo
	text_offset=$$(readelf -S $@ | grep " .text " | tr -s ' ' | sed -e "s/.*\.//g" | cut -d' ' -f4) && \
	puts_offset=$$(readelf -r $@ | grep "puts$$" | cut -d' ' -f1) && \
	dd if=/dev/zero of=$@ bs=1 seek=$$((0x$$text_offset+0x$$puts_offset)) count=4 conv=notrunc
	objdump -d -r $@ | grep -B1 R_
	@echo

FORCE:

clean:
	rm -rf $(OBJS)
