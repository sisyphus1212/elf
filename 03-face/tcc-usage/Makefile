
SRCS   = $(wildcard *.c)
EXEC   = $(basename $(SRCS))

all: dep $(EXEC)

run: dep FORCE
	tcc -run $(SRCS)

dep:
	@which tcc >/dev/null 2>&1 || \
	(sudo apt-get update -y && sudo apt-get install -y tcc || true)

%: %.c FORCE
	tcc -o $@ $<
	size $@
	wc -c $@

readelf: $(EXEC)
	readelf -l hello

FORCE:

clean:
	rm -rf $(EXEC)
