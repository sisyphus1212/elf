
# How to get 45B size

Notes: The result differs from gcc versions.

## pie.s

Encode strings data into .text section with `get_eip (_print)` logic.

    $ make pie
    as --32 -g -o pie.o pie.s
    ld -m elf_i386 -o pie pie.o
    wc -c pie
    1100 pie
    strip -s pie
    wc -c pie
    248 pie
    dd if=pie of=pie.strip bs=1 count=$((0x$(readelf -S pie | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
    111+0 records in
    111+0 records out
    111 bytes copied, 0.00029861 s, 372 kB/s
    mv pie.strip pie
    chmod +x pie
    wc -c pie
    111 pie
    PATH=$PATH:./ pie hello 0 0 0; echo ; echo $?

    0

## inst-opt.s

Using shorter encoded instructions to get less bytes.

    $ make inst-opt
    as --32 -g -o inst-opt.o inst-opt.s
    ld -m elf_i386 -o inst-opt inst-opt.o
    wc -c inst-opt
    1156 inst-opt
    strip -s inst-opt
    wc -c inst-opt
    296 inst-opt
    dd if=inst-opt of=inst-opt.strip bs=1 count=$((0x$(readelf -S inst-opt | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
    110+0 records in
    110+0 records out
    110 bytes copied, 0.000367793 s, 299 kB/s
    mv inst-opt.strip inst-opt
    chmod +x inst-opt
    wc -c inst-opt
    110 inst-opt
    PATH=$PATH:./ inst-opt hello 0 0 0; echo ; echo $?
 
    0


## data-from-args.s

Accept string setting from arguments, instead of encoding the string in elf itself.

    $ make data-from-args
    as --32 -g -o data-from-args.o data-from-args.s
    ld -m elf_i386 -o data-from-args data-from-args.o
    wc -c data-from-args
    1064 data-from-args
    strip -s data-from-args
    wc -c data-from-args
    236 data-from-args
    dd if=data-from-args of=data-from-args.strip bs=1 count=$((0x$(readelf -S data-from-args | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
    98+0 records in
    98+0 records out
    98 bytes copied, 0.000216709 s, 452 kB/s
    mv data-from-args.strip data-from-args
    chmod +x data-from-args
    wc -c data-from-args
    98 data-from-args
    PATH=$PATH:./ data-from-args hello 0 0 0; echo ; echo $?

    0

## hello.s

Linux kernel calls `ELF_PLAT_INIT` and inits many registers as zero for us, no
need to set them to zero again and no need to set the higher half-register.

    $ make hello
    as --32 -g -o hello.o hello.s
    ld -m elf_i386 -o hello hello.o
    wc -c hello
    972 hello
    strip -s hello
    wc -c hello
    232 hello
    dd if=hello of=hello.strip bs=1 count=$((0x$(readelf -S hello | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
    94+0 records in
    94+0 records out
    94 bytes copied, 0.000248977 s, 378 kB/s
    mv hello.strip hello
    chmod +x hello
    wc -c hello
    94 hello
    PATH=$PATH:./ hello hello 0 0 0; echo ; echo $?

     

## nihao.s

The `binary` version of hello.s, no need to move the code and the program header
table manually, simply put them at the required positions.

need ld's `--oformat=binary` option to link it.

This file is the same as 01-init/hello-asm/hello.s, it can be compiled with gcc directly:

    $ make nihao
    as --32 -g -o nihao.o nihao.s
    ld -m elf_i386 --oformat=binary -o nihao nihao.o
    PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:...:./ nihao hello 0 0 0; echo ; echo $?
    nihao
    0

    $ wc -c nihao
    45

    $ gcc -m32 -Wl,--oformat=binary -nostdlib -nostartfiles -o nihao nihao.s

* -nostdlib, means no stanard libraries used, no libc is required.
* -nostartfiles, means not link the startup files, such as crt1.o, crti.o, crtn.o ...

## binaries

### hello.merged-phdr-to-fileheader

moved the program header table to elf header

    $ hexdump -C staged/hello.merged-phdr-to-fileheader
    00000000  7f 45 4c 46 01 00 00 00  00 00 00 00 00 10 00 00  |.ELF............|
    00000010  03 00 06 00 54 10 00 00  54 10 00 00 04 00 00 00  |....T...T.......|
    00000020  ff ff ff ff ff ff ff ff  ff ff 20 00 01 00 ff ff  |.......... .....|
    00000030  ff ff ff ff dd dd dd dd  dd dd dd dd dd dd dd dd  |................|
    00000040  dd dd dd dd dd dd dd dd  dd dd dd dd dd dd dd dd  |................|
    00000050  dd dd dd dd 5a 59 6a 04  58 31 db cd 80 6a 01 e2  |....ZYj.X1...j..|
    00000060  f7                                                |.|
    00000061

### hello.merged-text-to-file-header

moved the code to elf header

    $ hexdump -C staged/hello.merged-text-to-file-header
    00000000  7f 45 4c 46 01 00 00 00  00 00 00 00 00 10 00 00  |.ELF............|
    00000010  03 00 06 00 20 10 00 00  20 10 00 00 04 00 00 00  |.... ... .......|
    00000020  5a 59 31 db 6a 01 6a 04  eb 04 20 00 01 00 58 cd  |ZY1.j.j... ...X.|
    00000030  80 e2 fb                                          |...|
    00000033


### hello.merged-all-to-45-bytes

moved all to first 45 bytes of elf header

    $ hexdump -C staged/hello.merged-all-to-45bytes
    00000000  7f 45 4c 46 01 00 00 00  00 00 00 00 00 10 00 00  |.ELF............|
    00000010  03 00 06 00 20 10 00 00  20 10 00 00 04 00 00 00  |.... ... .......|
    00000020  5a 59 b0 04 cd 80 b0 01  cd 80 20 00 01           |ZY........ ..|
    0000002d

## Demonstration

Added a demo for how to compile it with gcc and edit the binary with hexedit.

    http://showterm.io/896a3049fe1596fd9af84
