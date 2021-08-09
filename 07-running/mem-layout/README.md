

# 比较经典布局和灵活布局的区别

## 经典布局

    $ ulimit -s unlimited
    $ make
    cc -m32 -g -Tld.script -o layout layout.c
    ./layout
    ===== memory map =====
    .text:	0x8048000->0x8048a18 (__executable_start, code text)
    .data:	0x804a048->0x804a050 (__data_start, initilized data)
    .bss: 	0x804a050->0x804b024 (__bss_start, uninitilized data)
    heap: 	0x8fb4410->0x8fccab0 (address of the malloced space)
    shm  :	0x555b1000->0x555c96a0 (address of shared memory)
    libs: 	 <--0x55622670--> (address of function in libs)
    mmap: 	 <--0x555ca000--> (address of mmaped anon space)
    stack:	 <--0xffe24f10--> (address of local variables)
    arg:  	0xffe24ff4 (address of arguments)
    env:  	0xffe24ffc (address of environment variables)
    08048000-08049000 r-xp 00000000 08:11 1711803    labs/linux-lab/examples/360-elf/07-running/mem-layout/layout
    08049000-0804a000 r--p 00000000 08:11 1711803    labs/linux-lab/examples/360-elf/07-running/mem-layout/layout
    0804a000-0804b000 rw-p 00001000 08:11 1711803    labs/linux-lab/examples/360-elf/07-running/mem-layout/layout
    0804b000-0804c000 rw-p 00000000 00:00 0
    08fb4000-08fd5000 rw-p 00000000 00:00 0          [heap]
    55587000-555aa000 r-xp 00000000 08:01 1578396    /lib/i386-linux-gnu/ld-2.23.so
    555aa000-555ab000 r--p 00022000 08:01 1578396    /lib/i386-linux-gnu/ld-2.23.so
    555ab000-555ac000 rw-p 00023000 08:01 1578396    /lib/i386-linux-gnu/ld-2.23.so
    555ac000-555af000 r--p 00000000 00:00 0          [vvar]
    555af000-555b0000 r-xp 00000000 00:00 0          [vdso]
    555b0000-555b1000 rw-p 00000000 00:00 0
    555b1000-555ca000 rw-s 00000000 00:05 14974995   /SYSV00000000 (deleted)
    555ca000-555cd000 r--p 00000000 00:00 0
    555d9000-55789000 r-xp 00000000 08:01 1578410    /lib/i386-linux-gnu/libc-2.23.so
    55789000-5578b000 r--p 001af000 08:01 1578410    /lib/i386-linux-gnu/libc-2.23.so
    5578b000-5578c000 rw-p 001b1000 08:01 1578410    /lib/i386-linux-gnu/libc-2.23.so
    5578c000-55790000 rw-p 00000000 00:00 0
    ffe06000-ffe28000 rw-p 00000000 00:00 0          [stack]


## 灵活布局（默认）

    $ ulimit -s 8192
    $ make
    cc -m32 -g -Tld.script -o layout layout.c
    ./layout
    ===== memory map =====
    .text:	0x8048000->0x8048a18 (__executable_start, code text)
    .data:	0x804a048->0x804a050 (__data_start, initilized data)
    .bss: 	0x804a050->0x804b024 (__bss_start, uninitilized data)
    heap: 	0x835b410->0x8373ab0 (address of the malloced space)
    shm  :	0xf7764000->0xf777c6a0 (address of shared memory)
    libs: 	 <--0xf75e8670--> (address of function in libs)
    mmap: 	 <--0xf7761000--> (address of mmaped anon space)
    stack:	 <--0xff8e71c0--> (address of local variables)
    arg:  	0xff8e72a4 (address of arguments)
    env:  	0xff8e72ac (address of environment variables)
    08048000-08049000 r-xp 00000000 08:11 1711803    /labs/linux-lab/examples/360-elf/07-running/mem-layout/layout
    08049000-0804a000 r--p 00000000 08:11 1711803    /labs/linux-lab/examples/360-elf/07-running/mem-layout/layout
    0804a000-0804b000 rw-p 00001000 08:11 1711803    /labs/linux-lab/examples/360-elf/07-running/mem-layout/layout
    0804b000-0804c000 rw-p 00000000 00:00 0
    0835b000-0837c000 rw-p 00000000 00:00 0          [heap]
    f759e000-f759f000 rw-p 00000000 00:00 0
    f759f000-f774f000 r-xp 00000000 08:01 1578410    /lib/i386-linux-gnu/libc-2.23.so
    f774f000-f7751000 r--p 001af000 08:01 1578410    /lib/i386-linux-gnu/libc-2.23.so
    f7751000-f7752000 rw-p 001b1000 08:01 1578410    /lib/i386-linux-gnu/libc-2.23.so
    f7752000-f7755000 rw-p 00000000 00:00 0
    f7761000-f7764000 r--p 00000000 00:00 0
    f7764000-f777d000 rw-s 00000000 00:05 15007763   /SYSV00000000 (deleted)
    f777d000-f777e000 rw-p 00000000 00:00 0
    f777e000-f7781000 r--p 00000000 00:00 0          [vvar]
    f7781000-f7782000 r-xp 00000000 00:00 0          [vdso]
    f7782000-f77a5000 r-xp 00000000 08:01 1578396    /lib/i386-linux-gnu/ld-2.23.so
    f77a5000-f77a6000 r--p 00022000 08:01 1578396    /lib/i386-linux-gnu/ld-2.23.so
    f77a6000-f77a7000 rw-p 00023000 08:01 1578396    /lib/i386-linux-gnu/ld-2.23.so
    ff8c7000-ff8e9000 rw-p 00000000 00:00 0          [stack]


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
