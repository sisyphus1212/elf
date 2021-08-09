
SRCS   = $(wildcard *.asm)
EXEC   = $(addsuffix .exe, $(basename $(SRCS)))

all: winehq $(EXEC)
	@$(foreach e, $(EXEC), echo "Running $(e) with wine" && wine $(e); echo "Return value: $$?";)

# ref: https://tecadmin.net/how-to-install-wine-on-ubuntu-20-04/
winehq:
	@which wine >/dev/null 2>&1 || \
	(sudo dpkg --add-architecture i386 && \
	sudo apt-get install -y gpg-agent && \
	wget -qO - https://dl.winehq.org/wine-builds/winehq.key | sudo apt-key add - && \
	sudo apt-add-repository 'deb https://dl.winehq.org/wine-builds/ubuntu/ $(shell lsb_release -cs) main' && \
	sudo apt-get update -y && \
	sudo apt-get install -y winehq-stable \
	|| true)

%.exe: %.asm
	nasm -f bin $< -o $@

clean:
	rm -rf $(EXEC)
