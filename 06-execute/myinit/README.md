
# 修改 Linux 系统的第一个启动程序

## 演示视频

* [交叉编译 tinyshell 并运行](http://showterm.io/584155ca7da78c41d8b46)
* [在 arm/vexpress-a9 上把 tinysh 当 init 进程跑](http://showterm.io/99157bb9bff68cda3e8fc)

## 操作过程

可以通过 `init` 内核参数指定，例如：

    init=/bin/bash

在 Linux Lab 下实验，非常简单：

    $ cd /path/to/linux-lab
    $ make B=aarch64/virt
    $ make boot XKCLI="init=/bin/bash"
    ...
    bash-4.3 #

也可以把自己写的 Shell 交叉编译后，放进去：

    $ cd ../tinyshell
    $ make arm

    tiny sh>> ls

    Makefile  README.md  tinysh  tinysh.c  tinysh.i  tinysh.o  tinysh.s

    tiny sh>> quit

如果要放到板子上跑，需要静态编译，避免安装额外的库，静态编译的可以直接运行：

    $ make arm-static

    tiny sh>> ls
 
然后用 arm/vexpress-a9 的板子跑：

    $ cd /path/to/linux-lab
    $ make B=arm/vexpress-a9
    $ cp src/examples/360-elf/06-execute/tinyshell/tinysh system/
    $ make root-install
    $ make boot ROOTDEV=/dev/nfs XKCLI=/tinysh

    tinysh >> ls

    tools

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
