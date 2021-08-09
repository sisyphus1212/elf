
# Running a.out

gcc 新版本早已不再支持 a.out 格式的输出，现在唯一能找到的编译器是 Linux 0.11 Lab 中的。

可以通过 0.11 Lab 先编译出 a.out 格式，然后再放到最新的 Linux 上运行。

不过 Linux 5.1 已经开始删除 a.out，需要使用的话，得 revert 掉两个 patch，然后再把 `BINFMT_AOUT` 编译选项打开才能运行 a.out 文件。

详细用法请参考 [goodbye-aout.md](http://tinylab.org/goodbye-a.out/) 和 [演示视频](http://showterm.io/58a0ba66b94d15ae0a324)。

## 在 Linux 0.11 Lab 下进行 C 语言开发

先参照上述资料在 Linux Lab 下准备好 [Linux 0.11 Lab](https://gitee.com/tinylab/linux-0.11-lab) 的源代码，确保放在 `/labs/linux-0.11-lab` 下。

    $ cd /labs/
    $ git clone https://gitee.com/tinylab/linux-0.11-lab.git
    $ cd linux-0.11-lab

接着挂载文件系统，并准备好一个简单的 hello.c（可以把当前目录下的复制进去）：

    $ make mount-hd
    $ cd rootfs/_hda/usr/root
    $ sudo vim hello.c
    #include <stdio.h>

    int main(void)
    {
        printf("Hello.");
        return 0;
    }

    $ make umount-hd 

极个别系统如果不能执行 `make mount-hd`，需要确认本机是否有 minix 内核模块，没有的话需要手动编译一个，可参考 [演示视频](http://showterm.io/25e2f3c26cc0d7f449c1a)。

在 Linux Lab 中下载内核源码可以用：

    $ cd /path/to/linux-lab
    $ make kernel-download

接着启动 Linux 0.11:

    $ make boot-hd

启动以后，进去 Linux 0.11 控制台，先创建一个缺失的临时目录：

    $ mkdir /tmp

然后，按照分解动作预处理、编译、汇编、链接程序：

    $ gcc -E hello.c > hello.i
    $ gcc -S hello.i
    $ gcc -c hello.s
    $ gcc -o hello hello.o

## 查看汇编语言

    $ cat hello.s
    	.file	"hello.i"
    gcc_compiled.:
    .text
    LC0:
    	.ascii "Hello.\0"
    	.align 2
    .globl _main
    _main:
    	pushl %ebp
    	movl %esp,%ebp
    	pushl $LC0
    	call _printf
    	xorl %eax,%eax
    	jmp L1
    	.align 2
    L1:
    	leave
    	ret


## 查看 a.out 可重定位文件

在 Linux 0.11 中可以用 `objdump -hnrt` 查看程序格式，也可以回到 Linux 系统重新挂载后再用现代版本的 `objdump -x` 查看：

    $ make mount-hd
    $ cd rootfs/_hda/usr/root/
    $ sudo -s

    $ objdump -x hello.o
    
    hello.o:     file format a.out-i386-linux
    hello.o
    architecture: i386, flags 0x0000003d:
    HAS_RELOC, HAS_LINENO, HAS_DEBUG, HAS_SYMS, HAS_LOCALS
    start address 0x00000000
    
    Sections:
    Idx Name          Size      VMA               LMA               File off  Algn
      0 .text         00000020  00000000  00000000  00000020  2**3
                      CONTENTS, ALLOC, LOAD, RELOC, CODE
      1 .data         00000000  00000020  00000020  00000040  2**3
                      CONTENTS, ALLOC, LOAD, DATA
      2 .bss          00000000  00000020  00000020  00000000  2**3
                      ALLOC
    SYMBOL TABLE:
    00000000 l       .text 0000 00 04 gcc_compiled.
    00000008 g       .text 0000 00 05 _main
    00000000         *UND* 0000 00 01 _printf
    
    
    RELOCATION RECORDS FOR [.text]:
    OFFSET   TYPE              VALUE 
    00000011 DISP32            _printf
    0000000c 32                .text

## 查看 a.out 可执行文件格式

相对应地，可执行文件格式信息如下：

    $ objdump -x hello
    
    hello:     file format a.out-i386-linux
    hello
    architecture: i386, flags 0x000001be:
    EXEC_P, HAS_LINENO, HAS_DEBUG, HAS_SYMS, HAS_LOCALS, WP_TEXT, D_PAGED
    start address 0x00000000
    
    Sections:
    Idx Name          Size      VMA       LMA       File off  Algn
      0 .text         00003000  00000000  00000000  00000400  2**3
                      CONTENTS, ALLOC, LOAD, CODE
      1 .data         00001000  00003000  00003000  00003400  2**3
                      CONTENTS, ALLOC, LOAD, DATA
      2 .bss          00000000  00004000  00004000  00000000  2**3
                      ALLOC
    SYMBOL TABLE:
    00000000 l       .text 0000 00 04 /usr/local/lib/crt0.o
    00000000 l       .text 0000 00 04 __entry
    00000018 l       .text 0000 00 04 hello.o
    00000018 l       .text 0000 00 04 gcc_compiled.
    00000038 l       .text 0000 00 04 _f_printf.o


在 Linux 0.11 下面，a.out 用到的 `printf` 在生成可执行文件时已经确定了地址，原因是用到的库是静态链接库，printf 是被静态链接进来的。

可以用 `objdump -d hello-a.out | grep printf` 确认，也可以在 Linux 0.11 中用下面的命令查看过程。

    (linux 0.11) gcc -v -o hello hello.o
    /usr/local/lib/gcc-ld -o hello /usr/local/lib/crt0.o hello.o /usr/local/lib/gnulib -lc /usr/local/lib/gnulib
    (linux 0.11) file /usr/local/lib/gnulib
    random library gnulib: archive

那个时候，由于 a.out 对动态链接不友好，所以还在使用静态链接。实际上，经查阅资料，早期 Linux 版本用 a.out 的时候也有支持过共享库，总之呢是比较麻烦，具体怎么使用的，暂时不再考究。

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
