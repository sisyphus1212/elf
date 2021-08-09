
all: gcc tcc

tcc:
	[ ! -f /usr/bin/tcc ] && sudo apt-get update -y && sudo apt-get install -y tcc || true
	$(CUR)./hello-tcc.c

gcc:
	sudo cp gcc-run /usr/local/bin
	$(CUR)./hello-gcc.c
