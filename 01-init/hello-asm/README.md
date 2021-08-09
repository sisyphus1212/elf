
# Hello Assembly

This is the smallest printable ELF file in the world, only 45B size.

## Usage

### Build with as, ld and run it

    $ as --32 -o hello.o hello.s
    $ ld -melf_i386 --oformat=binary -o hello hello.o
    $ export PATH=./:$PATH
    $ hello 0 0 0 0
    hello

    $ wc -c hello
    45 hello

### Build with gcc and run it

    $ gcc -Wa,--32 -Wl,-melf_i386 -Wl,--oformat=binary -nostdlib -ffreestanding -o hello hello.s
    $ PATH=:./:$PATH hello 0 0 0 0
    hello
    $ ls
    hello.s Makefile

### Build intermediate files

    $ make hello.o

### Build with make

    $ make
    as --32 -o hello.o hello.s
    ld -melf_i386 --oformat=binary -o hello hello.o
    run hello
    hello

    Or

    $ make hello.gcc
    gcc -m32 -Wl,--oformat=binary -nostdlib -nostartfiles -o hello.gcc hello.s
    run hello.gcc
    hello.gcc

## Options

* -nostdlib, Do not use the standard system startup files or libraries when linking
* -ffreestanding, not necessary here, but helpful for future os kernel development, Assert that compilation targets a freestanding environment.  This implies -fno-builtin. A freestanding environment is one in which the standard library may not exist, and program startup may not necessarily be at "main".  The most obvious example is an OS kernel.
* -Wa,option -- pass options to assembler
* -Wl,option -- pass options to linker

## References

* 45B ELF Howto: <https://tinylab.gitbooks.io/cbook/zh/chapters/02-chapter8.html>

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
