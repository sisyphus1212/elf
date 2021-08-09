
# Compiling details

## 用 gcc 提供的选项编译

    $ export CUSTOM=n
    // 预处理
    $ make hello.i
    // 编译
    $ make hello.s
    // 汇编
    $ make hello.o
    // 链接
    $ make hello

## 用背后的实际工具

     $ export CUSTOM=y
    // 预处理
    $ make hello.i
    // 编译
    $ make hello.s
    // 汇编
    $ make hello.o
    // 链接
    $ make hello

## 注册 preinit/init/constructor/destructor/atext/fini 函数

查看 init/main/atexit/fini 调用顺序：

    $ make hello INIT_FINI=y
    $ ./hello
    init_array
    main
    atexit
    fini_array

新增 preinit, constructor, destructor，观察调用顺序：

    $ make hooks
    $ ./hooks
    preinit
    init
    constructor
    main
    my_atexit2
    my_atexit
    destructor
    fini

## 使用自定义链接脚本

    $ gcc -m32  -o hello hello.c -Wl,-Tld.script
    $ strip -R .note.gnu.build-id -R .gnu.version hello
    $ strip hello
    $ readelf -S hello | grep .shstrtab
      [17] .shstrtab STRTAB 00000000 00051c 00007c 00 0 0 1
    $ dd if=hello of=hello.strip bs=1 count=$((0x51c))

## 最新裁剪成果

    $ make
    1308 hello.strip


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
