
# How to make shared library executable

* [如何创建一个可执行的共享库](http://tinylab.org/exec-shlib/)
* [演示视频](http://showterm.io/b64ed600130a08217d216)

## make executable sharable

Note: This doesn't work with latest Ubuntu 20.04 and the according gcc and ld now.

    $ make libhello.so
    gcc -m32 -pie -fpie -rdynamic -o libhello.so hello.c
    ./libhello.so
    hello
    $ make main
    gcc -m32 -o main main.c -L./ -lhello
    LD_LIBRARY_PATH=:./ ./main
    hello...

## make shared library executable

    $ make clean
    $ make libhello.so DEFAULT=n
    gcc -m32 -shared -fpic -DEXEC_SHLIB -o libhello.so hello.c
    ./libhello.so
    hello.c 12: entry(): the real entry of shared library here.
    $ make main
    gcc -m32 -o main main.c -L./ -lhello
    LD_LIBRARY_PATH=:./ ./main
    hello...

## dlopen functions in executables

    $ make dlopen
    gcc -m32 -rdynamic -o dlopen dlopen.c -ldl
    ./dlopen
    hello...

## Notes

The ld-linux.so is /lib/i386-linux-gnu/ld-linux.so for libc6:i386 and /lib32/ld-linux.so for libc6-i386.

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
