
C_MAGIC := /* c magic */
C_MAGIC := $(shell echo "${C_MAGIC}" | tr -d '\n' | hexdump -v -e '"\\""x"1/1 "%02x"')

all: hello

hello: gcc-binfmt-magic

dep:
	[ ! -f /usr/sbin/update-binfmts ] && sudo apt-get update -y && sudo apt-get install -y binfmt-support || true

gcc-binfmt-magic: dep
	sudo cp gcc-run /usr/local/bin
	sudo update-binfmts --package gcc --install cscript /usr/local/bin/gcc-run --magic '${C_MAGIC}'
	./hello-gcc.c
	sudo update-binfmts --package gcc --remove cscript /usr/local/bin/gcc-run
