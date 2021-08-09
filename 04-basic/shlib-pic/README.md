
# Linux C 语言共享库如何做到位置无关

共享库有一个很重要的特征，就是可以被多个可执行文件共享：

* 共享意味着不仅磁盘上只有一份拷贝，加载到内存以后也只有一份拷贝，那么本身的代码部分不能被修改
* 同时意味着，需要能够映射在不同的虚拟地址空间，以便适应不同程序，避免地址冲突

这两点要求共享库的代码和数据都是位置无关的，这是怎么做到的呢？可参考 abi386-4.pdf P61~P62.

## 基本演示

    $ make
    gcc -m32 -shared -fpic -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-stack-protector -S hello.c
    gcc -m32 -shared -fpic -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-stack-protector -c -o hello.o hello.s
    gcc -m32 -shared -fpic -o libhello.so hello.o
    gcc -m32 -o main main.c -L./ -lhello
    LD_LIBRARY_PATH=:./ ./main
    hello
    objdump -d -j .text libhello.so | grep -A 14 "<hello>:"
    00000499 <hello>:
     499:    53                       push   %ebx
     49a:    83 ec 08                 sub    $0x8,%esp
     49d:    e8 1f 00 00 00           call   4c1 <__x86.get_pc_thunk.ax>
     4a2:    05 5e 1b 00 00           add    $0x1b5e,%eax
     4a7:    83 ec 0c                 sub    $0xc,%esp
     4aa:    8d 90 dc e4 ff ff        lea    -0x1b24(%eax),%edx
     4b0:    52                       push   %edx
     4b1:    89 c3                    mov    %eax,%ebx
     4b3:    e8 c8 fe ff ff           call   380 <puts@plt>
     4b8:    83 c4 10                 add    $0x10,%esp
     4bb:    90                       nop
     4bc:    83 c4 08                 add    $0x8,%esp
     4bf:    5b                       pop    %ebx
     4c0:    c3                       ret

    $ cat hello.s
        .file    "hello.c"
        .text
        .section    .rodata
    .LC0:
        .string    "hello"
        .text
        .globl    hello
        .type    hello, @function
    hello:
        pushl    %ebx
        subl    $8, %esp
        call    __x86.get_pc_thunk.ax
        addl    $_GLOBAL_OFFSET_TABLE_, %eax
        subl    $12, %esp
        leal    .LC0@GOTOFF(%eax), %edx
        pushl    %edx
        movl    %eax, %ebx
        call    puts@PLT
        addl    $16, %esp
        nop
        addl    $8, %esp
        popl    %ebx
        ret
        .size    hello, .-hello
        .section    .text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
        .globl    __x86.get_pc_thunk.ax
        .hidden    __x86.get_pc_thunk.ax
        .type    __x86.get_pc_thunk.ax, @function
    __x86.get_pc_thunk.ax:
        movl    (%esp), %eax
        ret
        .ident    "GCC: (Ubuntu 8.3.0-16ubuntu3~16.04) 8.3.0"
        .section    .note.GNU-stack,"",@progbits

## 进阶改造

核心代码可以改造为：

```
    call    __x86.get_pc_thunk.ax
.eip:
    ; 计算 eip + (.LC0 - .eip) 刚好指向内存中的数据 "hello" 所在位置
    movl    %eax, %ebx
    leal    (.LC0 - .eip)(%eax), %edx

    ; 计算 .got.plt 地址，_GLOBAL_OFFSET_TABLE_ 是相对 eip 的偏移，所以必须加上这个 offset：. - .eip
    addl    $_GLOBAL_OFFSET_TABLE_ + [. - .eip], %ebx
    subl    $12, %esp
    pushl   %edx
    call    puts@PLT
```

改造后的代码见 hello.new.s。

    $ make new
    gcc -m32 -g -shared -fpic -o libhello.so hello.new.s
    gcc -m32 -o main main.c -L./ -lhello
    LD_LIBRARY_PATH=:./ ./main
    hello
    objdump -d -j .text libhello.so | grep -A 14 "<hello>:"
    00000499 <hello>:
     499:	53                   	push   %ebx
     49a:	83 ec 08             	sub    $0x8,%esp
     49d:	e8 20 00 00 00       	call   4c2 <__x86.get_pc_thunk.ax>

    000004a2 <.eip>:
     4a2:	89 c3                	mov    %eax,%ebx
     4a4:	8d 90 3a 00 00 00    	lea    0x3a(%eax),%edx
     4aa:	81 c3 5e 1b 00 00    	add    $0x1b5e,%ebx
     4b0:	83 ec 0c             	sub    $0xc,%esp
     4b3:	52                   	push   %edx
     4b4:	e8 c7 fe ff ff       	call   380 <puts@plt>
     4b9:	83 c4 10             	add    $0x10,%esp
     4bc:	90                   	nop
     4bd:	83 c4 08             	add    $0x8,%esp

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
