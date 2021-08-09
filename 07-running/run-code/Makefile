
all: run clean

run:
	ls | grep -v Makefile | xargs -i make -C {}

clean:
	ls | grep -v Makefile | xargs -i make clean -C {}
