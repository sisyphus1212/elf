
# 各平台最小可打印字符串的二进制可执行文件

## Windows PE, 97

[What is the smallest windows pe executable](https://stackoverflow.com/questions/553029)

* 最小 PE 文件（32）: 97 bytes
* 最小 PE 文件（X64）: 268 bytes

实验步骤：

    $ cd pe
    $ make
    Running tinype32.exe with wine
    Return value: 42
    Running tinype32+.exe with wine
    Return value: 42

注意：在 Ubuntu 20.04 下直接安装 wine 似乎无法工作，当前 `make` 参考 [该文](https://tecadmin.net/how-to-install-wine-on-ubuntu-20-04/) 自动安装了 PPA 中的最新版本，安装过程较慢，如果不想耽误时间，可以直接中断。

## MachOSX Mach-O, 164

[Hello Mach-O](http://seriot.ch/hello_macho.php)：

* [tiny_mfeiri.asm](http://www.feiri.de/macho/): 164 字节
* [rev_mach-o.asm](http://www.0xcafebabe.it/2013/01/04/tiny-mach-0-are-fun/): 180 字节
* [micro_macho.zip](http://seriot.ch/texts/hello_macho/micro_macho.zip): 164 字节
* [tiny_kamils.s](https://stackoverflow.com/questions/32453849/minimal-mach-o-64-binary): 4096 字节

实验步骤：

    $ sudo apt-get install yasm
    $ cd mach-o
    $ make

说明：上述编译出来的是 32 位的，目前不能在 darling 下运行。

* [Darling](https://github.com/darlinghq/darling)，自行编译超级慢
* [Darling Docker](https://github.com/utensils/docker-darling)，在 4.4 内核编译失败

新增了独立文档：README-darling.md，欢迎体验。

## Linux ELF, 45

* [Tiny ELF 32/64 with nasm](https://blog.stalkr.net/2014/10/tiny-elf-3264-with-nasm.html)
* [A Whirlwind Tutorial on Creating Really Teensy ELF Executables for Linux](http://www.muppetlabs.com/~breadbox/software/tiny/teensy.html)：45 字节
* [打造史上最小可执行 ELF 文件](https://tinylab.gitbooks.io/cbook/zh/chapters/02-chapter8.html)：45 字节

实验步骤：

    $ cd elf/
    nasm -f bin tinyret42.asm -o tinyret42
    Running tinyret42
    Return value: 42
    as --32 -o tinyhello.o tinyhello.s
    ld -melf_i386 --oformat=binary -o tinyhello tinyhello.o
    Running tinyhello
    tinyhello


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
