
# Using gcc

这里介绍 gcc 的用法。

## -m64, -mx32, m32 比较

说明：-mx32 依赖一些额外的库，会自动安装；编译结果在不同系统和编译器下会有合理差异。

    $ make all
    Compiling with:  -m64
       text	   data	    bss	    dec	    hex	filename
       1160	    544	      8	   1712	    6b0	hello.-m64
    Compiling with:  -mx32
       text	   data	    bss	    dec	    hex	filename
       1061	    296	      4	   1361	    551	hello.-mx32
    Compiling with:  -m32
       text	   data	    bss	    dec	    hex	filename
       1098	    272	      4	   1374	    55e	hello.-m32

## 编译时 strip 掉 .symtab 和 .strtab

    $ make
    Compiling with:  -m32
    gcc  -m32 -o hello.-m32 hello.c
    size hello.-m32
       text	   data	    bss	    dec	    hex	filename
       1098	    272	      4	   1374	    55e	hello.-m32
    wc -c hello.-m32
    7184 hello.-m32

    $ make strip
    make -s one STRIP=-s
    Compiling with:  -m32
       text	   data	    bss	    dec	    hex	filename
       1098	    272	      4	   1374	    55e	hello.-m32
    5532 hello.-m32

## 编译时使用 -Os

注：这里的 hello.c 程序代码比较简单，已经没有优化的空间。可以尝试写一个复杂一点的算法来验证。

    $ make
    Compiling with:  -m32
    gcc   -m32 -o hello.-m32 hello.c
    size hello.-m32
       text	   data	    bss	    dec	    hex	filename
       1098	    272	      4	   1374	    55e	hello.-m32
    wc -c hello.-m32
    7184 hello.-m32
    $ make optsize
    make -s one OPTSIZE=-Os
    Compiling with:  -m32
       text	   data	    bss	    dec	    hex	filename
       1098	    272	      4	   1374	    55e	hello.-m32
    7184 hello.-m32


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
