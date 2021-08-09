
STD := standards

all: help

help:
	@echo "make std -- download standards"

std:
	@git submodule update --force --init --remote $(STD)

zip:
	git archive default --format=zip > ../360-elf-20210627.zip
