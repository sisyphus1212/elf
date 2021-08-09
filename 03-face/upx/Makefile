
CMD ?= /bin/ls

all: dep
	cp $(CMD) .
	upx -qq `basename $(CMD)`

dep:
	@which upx >/dev/null 2>&1 || (sudo apt-get update -y && sudo apt-get install -y upx || true)

clean:
	rm -rf ls
