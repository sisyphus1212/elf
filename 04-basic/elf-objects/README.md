
# ELF Objects 比较

## Relocables

    $ make hello.o

## Static Library

    $ make libhello.a

## Shared Objects

    $ make libhello.so

## Executables

    $ make hello

    and

    $ make hello.noc

## Shared and Executable Objects

    $ make hello.noc SHARED_EXEC_MANUAL=y

## Notes

The ld-linux.so is /lib/i386-linux-gnu/ld-linux.so for libc6:i386 and /lib32/ld-linux.so for libc6-i386.

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
