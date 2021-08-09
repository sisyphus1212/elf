
GCC_VERSION ?= $(shell ls /usr/bin/gcc-[0-9]* | sort -r -g | head -1 | cut -d '-' -f2)

M ?= -m32

SRCS   = $(wildcard *.c)
MOPT   = -m64 -mx32 -m32
EXEC   = $(basename $(SRCS))

one: $(EXEC) FORCE

strip:
	make -s one STRIP=-s

optsize:
	make -s one OPTSIZE=-Os

all: install-all
	@$(foreach m, $(MOPT), make -s M=$m;)

%: %.c FORCE
	@echo "Compiling with: " $(M)
	gcc $(STRIP) $(OPTSIZE) $(M) -o $@.$(M) $<
	size $@.$(M)
	wc -c $@.$(M)

clean:
	rm -rf $(EXEC) $(EXEC).-m*

install-elfutils:
	@[ ! -x /usr/bin/eu-readelf ] && \
	sudo apt-get -y update && \
	sudo apt-get install -y elfutils || true

install-all: install-elfutils
	@dpkg -xL libc6-dev-x32 >/dev/null 2>&1 || \
	(sudo apt-get update -y && \
	sudo apt-get install -y libc6-x32 libc6-dev-x32 libx32gcc-$(GCC_VERSION)-dev || true)

FORCE:
