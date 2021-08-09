
# Sections operation

该实验演示如何通过不同方式给程序新增/调整数据。

## 三种方法

    $ make
    gcc -m32 -shared -fpic -o libhello-inline-asm.so inline-asm.c
    ./libhello-inline-asm.so
    hello
    gcc -m32 -shared -fpic -o libhello-c-attribute.so c-attribute.c
    ./libhello-c-attribute.so
    hello
    bash -c 'echo -en "/lib32/ld-linux.so.2\x00" > interp.section.txt'
    gcc -m32 -shared -fpic -c -o objcopy.o objcopy.c
    objcopy --add-section .interp=interp.section.txt objcopy.o --set-section-flags .interp=alloc,readonly
    gcc -m32 -shared -fpic -o libhello-objcopy.so objcopy.o #-Tld.script
    ./libhello-objcopy.so
    hello

## 更新和替换

    $ make update
    gcc -m32 -shared -fpic -o libhello-c-attribute.so c-attribute.c
    ./libhello-c-attribute.so
    objcopy --dump-section .interp=interp.txt libhello-c-attribute.so
    sed -i -e "s%/lib32/ld-linux.so.2%/lib32/ld-2.31.so%g" interp.txt
    objcopy --update-section .interp=interp.txt libhello-c-attribute.so
    chmod a+x libhello-c-attribute.so
    ./libhello-c-attribute.so


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
