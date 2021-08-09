
# Using a mini dl

来自台湾的 jserv 老师有写了一个 minimal 的 dl，支持 X86_64, ARM 和 Aarch64，只是实现了一个动态链接库的核心函数，需要自己写成工具，有提供测试代码。

* loader.c: `dloader_p o = DLoader.load("test_lib.so");`
* test_loader.c: 核心函数的使用演示，加载并运行
* test_libc: 一个用于测试的函数库

X86 支持还没有，正好可以来练手！

## 使用

默认使用：

    $ git clone https://github.com/jserv/min-dl
    $ cd min-dl
    $ make
    gcc -std=gnu99 -Wall -Werror -g -D_GNU_SOURCE -DPROG_HEADER=prog_header -fvisibility=hidden -shared -fPIC -c test_lib.c \
    	-o out/test_lib.o -MMD -MF out/test_lib.o.d
    gcc -shared -Wl,--entry=prog_header -Wl,-z,defs -nostdlib \
    	out/test_lib.o -o out/test_lib.so
    gcc -std=gnu99 -Wall -Werror -g -D_GNU_SOURCE -DPROG_HEADER=prog_header -o out/loader.o -MMD -MF out/loader.o.d -c loader.c
    gcc -std=gnu99 -Wall -Werror -g -D_GNU_SOURCE -DPROG_HEADER=prog_header -o out/test_loader.o -MMD -MF out/test_loader.o.d -c test_loader.c
    gcc -o out/loader out/loader.o out/test_loader.o

    $ cd out/
    $ ./loader      # 默认加载的是用来测试一个库 test_lib.so，路径和名字都写死了，不能传递参数
    Test exported functions >
    OK!
    Test imported functions >
    resolver called for func #0
    resolver called for func #1
    OK!

For ARM，需要指定编译器，也可以直接进 Makefile 修改：

    $ make arm


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
