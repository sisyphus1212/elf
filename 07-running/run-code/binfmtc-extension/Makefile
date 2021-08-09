
all: gcc-binfmt-extension

dep:
	[ ! -f /usr/sbin/update-binfmts ] && sudo apt-get update -y && sudo apt-get install -y binfmt-support || true

gcc-binfmt-extension: dep
	sudo cp gcc-run /usr/local/bin
	sudo update-binfmts --package gcc --install cscript /usr/local/bin/gcc-run --extension c
	./hello-gcc.c
	sudo update-binfmts --package gcc --remove cscript /usr/local/bin/gcc-run
