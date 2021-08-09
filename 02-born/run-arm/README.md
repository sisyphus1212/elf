
# Running ARM ELF

这里演示如何在 X86 下直接运行 ARM 的二进制 ELF 可执行文件。

## 编译生成 ARM ELF 并运行

先在 Linux Lab 下编译获得一个 ARM ELF 文件：

    $ cd arm/
    $ arm-linux-gnueabi-gcc -nostdlib -o arm-hello arm-hello.s
    $ file arm-hello
    arm-hello: ELF 32-bit LSB  executable, ARM, EABI5 version 1 (SYSV), statically linked, BuildID[sha1]=f54ef2cf775deadcff80459b82524143618bb5aa, not stripped

## 安装 ARM ELF 静态翻译工具 qemu-arm

说明：请在 Ubuntu host 下做如下实验，如需在 Linux Lab 中完成，需要额外安装 qemu-user-binfmt。

    $ sudo apt-get update
    $ sudo apt-get install qemu-user qemu-user-static binfmt-support

## 注册 ARM ELF 可执行文件格式

可以参考已经注册的 qemu-arm 再注册一个 armelf，也可以参考 [scripts/qemu-binfmt-conf.sh][1]：

    $ cat /var/lib/binfmts/qemu-arm
    qemu-user-static
    magic
    0
    \x7f\x45\x4c\x46\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x28\x00
    \xff\xff\xff\xff\xff\xff\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff\xff
    /usr/bin/qemu-arm-static

    yes

    $ sudo update-binfmts --package armelf --install armelf /usr/bin/qemu-arm-static --magic '\x7f\x45\x4c\x46\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x28\x00' --mask '\xff\xff\xff\xff\xff\xff\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff\xff' --credentials yes

    $ cat /var/lib/binfmts/armelf
    armelf
    magic
    0
    \x7f\x45\x4c\x46\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x28\x00
    \xff\xff\xff\xff\xff\xff\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff\xff
    /usr/bin/qemu-arm-static

    yes

注册后可以这样删除：

    $ sudo update-binfmts --package armelf --remove armelf /usr/bin/qemu-arm-static

## 运行 ARM ELF

    $ ./arm-hello
    Hello, ARM!

## 一键编译和运行

    $ make
    arm-linux-gnueabi-as -o arm-hello.o arm-hello.s
    arm-linux-gnueabi-ld -o arm-hello arm-hello.o
    Hello, ARM!

## 在 X86 Linux 系统下运行 ARM Linux 系统

原理类似，只需要把 `/usr/bin/qemu-arm-static` 复制到 ARM Linux 文件系统的 `usr/bin` 目录下，即可用 chroot 进去使用。

在主机 Linux 系统下，用 Linux Lab 的工具下载一个 ARM 文件系统：

    $ cd $(path-to)/linux-lab
    $ tools/rootfs/docker/extract.sh tinylab/arm32v7-ubuntu arm

并运行：

    $ tools/rootfs/docker/chroot.sh tinylab/arm32v7-ubuntu

或：

    $ tools/rootfs/docker/run.sh tinylab/arm32v7-ubuntu arm

启动后，用户名和密码都是 root

这样的话，在没有 ARM 开发板的情况下，也可以学习嵌入式 ARM Linux 系统开发。

当然，也可以用更重一点的方式，整机模拟器，比如说 qemu, skyeye 等模拟器，如果不涉及到板级模拟，用 qemu-user 就够了，当然，也可以试一试 [Unicorn][2]。

[1]: https://github.com/qemu/qemu/blob/master/scripts/qemu-binfmt-conf.sh
[2]: http://www.unicorn-engine.org/docs/beyond_qemu.html

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
