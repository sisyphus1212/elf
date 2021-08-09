
# How C variables work

* [演示视频](http://showterm.io/4c9e0ccce59d3b6db863a)

## Usage

    $ make
    gcc -fno-stack-protector -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-pie -no-pie -m32 -Wall -Werror -E -o hello.i hello.c
    gcc -fno-stack-protector -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-pie -no-pie -m32 -Wall -Werror -S -o hello.s hello.c
    gcc -fno-stack-protector -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-pie -no-pie -m32 -Wall -Werror -c -o hello.o hello.c
    gcc -fno-stack-protector -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-pie -no-pie -m32 -Wall -Werror  -o hello hello.c
    argc = 1, addr of argc = 0xfffa0ec0
    argv = hello, addr of argv = 0xfffa0f54
    m = 0, addr of m = 0x804a02c
    n = 1000, addr of n = 0x804a01c
    a = 0, addr of a = 0x804a034
    b = 10000, addr of b = 0x804a020
    i = 0, addr of i = 0x804a030
    j = 10, addr of j = 0x804a024
    x = 134513961, addr of x = 0xfffa0e8c
    y = 100, addr of y = 0xfffa0e88
    z = 33, in register, no addr

    $ readelf -S hello | grep 804a
      [23] .got.plt          PROGBITS        0804a000 001000 000014 04  WA  0   0  4
      [24] .data             PROGBITS        0804a014 001014 000014 00  WA  0   0  4
      [25] .bss              NOBITS          0804a028 001028 000010 00  WA  0   0  4

    /* Memory Layout */
    argc = 1, addr of argc = 0xfffa0ec0     /* stack, arg1 of main */
    argv = hello, addr of argv = 0xfffa0f54 /* stack, arg2 of main */
    m = 0, addr of m = 0x804a02c            /* .bss,  static int m;        local */
    n = 1000, addr of n = 0x804a01c         /* .data, static int n = 1000; local */
    a = 0, addr of a = 0x804a034            /* .bss,  int a;               global */
    b = 10000, addr of b = 0x804a020        /* .data, int b = 10000;       global */
    i = 0, addr of i = 0x804a030            /* .bss,  static int i;        hello(); */
    j = 10, addr of j = 0x804a024           /* .data, static int j = 10;   hello(); */
    x = 134513914, addr of x = 0xffbf3ecc   /* stack, int x;               hello(); */
    y = 100, addr of y = 0xffbf3ec8         /* stack, int y = 100;         hello(); */
    z = 33, in register, no addr            /* register, int z = 33;       hello(); */

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
