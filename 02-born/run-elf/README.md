
# Running elf

同样准备一个极简的 hello.c，用 `objdump -x`，分别查看 hello.o 和 hello 如下：

    $ cat hello.c
    #include <stdio.h>

    int main(void)
    {
    	printf("hello\n");

    	return 0;
    }

    $ make

    or

    $ gcc -m32 -c hello.c
    $ gcc -m32 -o hello hello.o

## 用 objdump 查看可重定位文件


    $ objdump -x hello.o


    hello.o:     file format elf32-i386
    hello.o
    architecture: i386, flags 0x00000011:
    HAS_RELOC, HAS_SYMS
    start address 0x00000000

    Sections:
    Idx Name          Size      VMA       LMA       File off  Algn
      0 .text         0000002e  00000000  00000000  00000034  2**0
                      CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
      1 .data         00000000  00000000  00000000  00000062  2**0
                      CONTENTS, ALLOC, LOAD, DATA
      2 .bss          00000000  00000000  00000000  00000062  2**0
                      ALLOC
      3 .rodata       00000006  00000000  00000000  00000062  2**0
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      4 .comment      0000002b  00000000  00000000  00000068  2**0
                      CONTENTS, READONLY
      5 .note.GNU-stack 00000000  00000000  00000000  00000093  2**0
                      CONTENTS, READONLY
      6 .eh_frame     00000044  00000000  00000000  00000094  2**2
                      CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
    SYMBOL TABLE:
    00000000 l    df *ABS*	00000000 hello.c
    00000000 l    d  .text	00000000 .text
    00000000 l    d  .data	00000000 .data
    00000000 l    d  .bss	00000000 .bss
    00000000 l    d  .rodata	00000000 .rodata
    00000000 l    d  .note.GNU-stack	00000000 .note.GNU-stack
    00000000 l    d  .eh_frame	00000000 .eh_frame
    00000000 l    d  .comment	00000000 .comment
    00000000 g     F .text	0000002e main
    00000000         *UND*	00000000 puts


    RELOCATION RECORDS FOR [.text]:
    OFFSET   TYPE              VALUE
    00000015 R_386_32          .rodata
    0000001a R_386_PC32        puts


    RELOCATION RECORDS FOR [.eh_frame]:
    OFFSET   TYPE              VALUE
    00000020 R_386_PC32        .text

## 用 objdump 查看可执行文件

    $ objdump -x hello

    hello:     file format elf32-i386
    hello
    architecture: i386, flags 0x00000112:
    EXEC_P, HAS_SYMS, D_PAGED
    start address 0x08048310

    Program Header:
        PHDR off    0x00000034 vaddr 0x08048034 paddr 0x08048034 align 2**2
             filesz 0x00000120 memsz 0x00000120 flags r-x
      INTERP off    0x00000154 vaddr 0x08048154 paddr 0x08048154 align 2**0
             filesz 0x00000013 memsz 0x00000013 flags r--
        LOAD off    0x00000000 vaddr 0x08048000 paddr 0x08048000 align 2**12
             filesz 0x000005b0 memsz 0x000005b0 flags r-x
        LOAD off    0x00000f0c vaddr 0x08049f0c paddr 0x08049f0c align 2**12
             filesz 0x00000110 memsz 0x00000114 flags rw-
     DYNAMIC off    0x00000f14 vaddr 0x08049f14 paddr 0x08049f14 align 2**2
             filesz 0x000000e8 memsz 0x000000e8 flags rw-
        NOTE off    0x00000168 vaddr 0x08048168 paddr 0x08048168 align 2**2
             filesz 0x00000044 memsz 0x00000044 flags r--
    EH_FRAME off    0x000004b8 vaddr 0x080484b8 paddr 0x080484b8 align 2**2
             filesz 0x0000002c memsz 0x0000002c flags r--
       STACK off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**4
             filesz 0x00000000 memsz 0x00000000 flags rw-
       RELRO off    0x00000f0c vaddr 0x08049f0c paddr 0x08049f0c align 2**0
             filesz 0x000000f4 memsz 0x000000f4 flags r--

    Dynamic Section:
      NEEDED               libc.so.6
      INIT                 0x080482a8
      FINI                 0x08048494
      INIT_ARRAY           0x08049f0c
      INIT_ARRAYSZ         0x00000004
      FINI_ARRAY           0x08049f10
      FINI_ARRAYSZ         0x00000004
      GNU_HASH             0x080481ac
      STRTAB               0x0804821c
      SYMTAB               0x080481cc
      STRSZ                0x0000004a
      SYMENT               0x00000010
      DEBUG                0x00000000
      PLTGOT               0x0804a000
      PLTRELSZ             0x00000010
      PLTREL               0x00000011
      JMPREL               0x08048298
      REL                  0x08048290
      RELSZ                0x00000008
      RELENT               0x00000008
      VERNEED              0x08048270
      VERNEEDNUM           0x00000001
      VERSYM               0x08048266

    Version References:
      required from libc.so.6:
        0x0d696910 0x00 02 GLIBC_2.0

    Sections:
    Idx Name          Size      VMA       LMA       File off  Algn
      0 .interp       00000013  08048154  08048154  00000154  2**0
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      1 .note.ABI-tag 00000020  08048168  08048168  00000168  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      2 .note.gnu.build-id 00000024  08048188  08048188  00000188  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      3 .gnu.hash     00000020  080481ac  080481ac  000001ac  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      4 .dynsym       00000050  080481cc  080481cc  000001cc  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      5 .dynstr       0000004a  0804821c  0804821c  0000021c  2**0
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      6 .gnu.version  0000000a  08048266  08048266  00000266  2**1
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      7 .gnu.version_r 00000020  08048270  08048270  00000270  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      8 .rel.dyn      00000008  08048290  08048290  00000290  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
      9 .rel.plt      00000010  08048298  08048298  00000298  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
     10 .init         00000023  080482a8  080482a8  000002a8  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, CODE
     11 .plt          00000030  080482d0  080482d0  000002d0  2**4
                      CONTENTS, ALLOC, LOAD, READONLY, CODE
     12 .plt.got      00000008  08048300  08048300  00000300  2**3
                      CONTENTS, ALLOC, LOAD, READONLY, CODE
     13 .text         00000182  08048310  08048310  00000310  2**4
                      CONTENTS, ALLOC, LOAD, READONLY, CODE
     14 .fini         00000014  08048494  08048494  00000494  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, CODE
     15 .rodata       0000000e  080484a8  080484a8  000004a8  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
     16 .eh_frame_hdr 0000002c  080484b8  080484b8  000004b8  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
     17 .eh_frame     000000cc  080484e4  080484e4  000004e4  2**2
                      CONTENTS, ALLOC, LOAD, READONLY, DATA
     18 .init_array   00000004  08049f0c  08049f0c  00000f0c  2**2
                      CONTENTS, ALLOC, LOAD, DATA
     19 .fini_array   00000004  08049f10  08049f10  00000f10  2**2
                      CONTENTS, ALLOC, LOAD, DATA
     20 .dynamic      000000e8  08049f14  08049f14  00000f14  2**2
                      CONTENTS, ALLOC, LOAD, DATA
     21 .got          00000004  08049ffc  08049ffc  00000ffc  2**2
                      CONTENTS, ALLOC, LOAD, DATA
     22 .got.plt      00000014  0804a000  0804a000  00001000  2**2
                      CONTENTS, ALLOC, LOAD, DATA
     23 .data         00000008  0804a014  0804a014  00001014  2**2
                      CONTENTS, ALLOC, LOAD, DATA
     24 .bss          00000004  0804a01c  0804a01c  0000101c  2**0
                      ALLOC
     25 .comment      0000002a  00000000  00000000  0000101c  2**0
                      CONTENTS, READONLY
    SYMBOL TABLE:
    08048154 l    d  .interp	00000000              .interp
    08048168 l    d  .note.ABI-tag	00000000              .note.ABI-tag
    08048188 l    d  .note.gnu.build-id	00000000              .note.gnu.build-id
    080481ac l    d  .gnu.hash	00000000              .gnu.hash
    080481cc l    d  .dynsym	00000000              .dynsym
    0804821c l    d  .dynstr	00000000              .dynstr
    08048266 l    d  .gnu.version	00000000              .gnu.version
    08048270 l    d  .gnu.version_r	00000000              .gnu.version_r
    08048290 l    d  .rel.dyn	00000000              .rel.dyn
    08048298 l    d  .rel.plt	00000000              .rel.plt
    080482a8 l    d  .init	00000000              .init
    080482d0 l    d  .plt	00000000              .plt
    08048300 l    d  .plt.got	00000000              .plt.got
    08048310 l    d  .text	00000000              .text
    08048494 l    d  .fini	00000000              .fini
    080484a8 l    d  .rodata	00000000              .rodata
    080484b8 l    d  .eh_frame_hdr	00000000              .eh_frame_hdr
    080484e4 l    d  .eh_frame	00000000              .eh_frame
    08049f0c l    d  .init_array	00000000              .init_array
    08049f10 l    d  .fini_array	00000000              .fini_array
    08049f14 l    d  .dynamic	00000000              .dynamic
    08049ffc l    d  .got	00000000              .got
    0804a000 l    d  .got.plt	00000000              .got.plt
    0804a014 l    d  .data	00000000              .data
    0804a01c l    d  .bss	00000000              .bss
    00000000 l    d  .comment	00000000              .comment
    00000000 l    df *ABS*	00000000              crtstuff.c
    08048350 l     F .text	00000000              deregister_tm_clones
    08048390 l     F .text	00000000              register_tm_clones
    080483d0 l     F .text	00000000              __do_global_dtors_aux
    0804a01c l     O .bss	00000001              completed.7493
    08049f10 l     O .fini_array	00000000              __do_global_dtors_aux_fini_array_entry
    08048400 l     F .text	00000000              frame_dummy
    08049f0c l     O .init_array	00000000              __frame_dummy_init_array_entry
    00000000 l    df *ABS*	00000000              hello.c
    00000000 l    df *ABS*	00000000              crtstuff.c
    080485ac l     O .eh_frame	00000000              __FRAME_END__
    00000000 l    df *ABS*	00000000
    08049f10 l       .init_array	00000000              __init_array_end
    08049f14 l     O .dynamic	00000000              _DYNAMIC
    08049f0c l       .init_array	00000000              __init_array_start
    080484b8 l       .eh_frame_hdr	00000000              __GNU_EH_FRAME_HDR
    0804a000 l     O .got.plt	00000000              _GLOBAL_OFFSET_TABLE_
    08048490 g     F .text	00000002              __libc_csu_fini
    00000000  w      *UND*	00000000              _ITM_deregisterTMCloneTable
    08048340 g     F .text	00000004              .hidden __x86.get_pc_thunk.bx
    0804a014  w      .data	00000000              data_start
    0804a01c g       .data	00000000              _edata
    08048494 g     F .fini	00000000              _fini
    0804a014 g       .data	00000000              __data_start
    00000000       F *UND*	00000000              puts@@GLIBC_2.0
    00000000  w      *UND*	00000000              __gmon_start__
    0804a018 g     O .data	00000000              .hidden __dso_handle
    080484ac g     O .rodata	00000004              _IO_stdin_used
    00000000       F *UND*	00000000              __libc_start_main@@GLIBC_2.0
    08048430 g     F .text	0000005d              __libc_csu_init
    0804a020 g       .bss	00000000              _end
    08048310 g     F .text	00000000              _start
    080484a8 g     O .rodata	00000004              _fp_hw
    0804a01c g       .bss	00000000              __bss_start
    08048402 g     F .text	0000002e              main
    0804a01c g     O .data	00000000              .hidden __TMC_END__
    00000000  w      *UND*	00000000              _ITM_registerTMCloneTable
    080482a8 g     F .init	00000000              _init


## 用 readelf -a hello.o 查看可重定位文件

    $ readelf -a hello.o
    
    ELF Header:
      Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
      Class:                             ELF32
      Data:                              2's complement, little endian
      Version:                           1 (current)
      OS/ABI:                            UNIX - System V
      ABI Version:                       0
      Type:                              REL (Relocatable file)
      Machine:                           Intel 80386
      Version:                           0x1
      Entry point address:               0x0
      Start of program headers:          0 (bytes into file)
      Start of section headers:          532 (bytes into file)
      Flags:                             0x0
      Size of this header:               52 (bytes)
      Size of program headers:           0 (bytes)
      Number of program headers:         0
      Size of section headers:           40 (bytes)
      Number of section headers:         13
      Section header string table index: 10
    
    Section Headers:
      [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
      [ 0]                   NULL            00000000 000000 000000 00      0   0  0
      [ 1] .text             PROGBITS        00000000 000034 00002e 00  AX  0   0  1
      [ 2] .rel.text         REL             00000000 00019c 000010 08   I 11   1  4
      [ 3] .data             PROGBITS        00000000 000062 000000 00  WA  0   0  1
      [ 4] .bss              NOBITS          00000000 000062 000000 00  WA  0   0  1
      [ 5] .rodata           PROGBITS        00000000 000062 000006 00   A  0   0  1
      [ 6] .comment          PROGBITS        00000000 000068 00002b 01  MS  0   0  1
      [ 7] .note.GNU-stack   PROGBITS        00000000 000093 000000 00      0   0  1
      [ 8] .eh_frame         PROGBITS        00000000 000094 000044 00   A  0   0  4
      [ 9] .rel.eh_frame     REL             00000000 0001ac 000008 08   I 11   8  4
      [10] .shstrtab         STRTAB          00000000 0001b4 00005f 00      0   0  1
      [11] .symtab           SYMTAB          00000000 0000d8 0000b0 10     12   9  4
      [12] .strtab           STRTAB          00000000 000188 000013 00      0   0  1
    Key to Flags:
      W (write), A (alloc), X (execute), M (merge), S (strings)
      I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
      O (extra OS processing required) o (OS specific), p (processor specific)
    
    There are no section groups in this file.
    
    There are no program headers in this file.
    
    Relocation section '.rel.text' at offset 0x19c contains 2 entries:
     Offset     Info    Type            Sym.Value  Sym. Name
    00000015  00000501 R_386_32          00000000   .rodata
    0000001a  00000a02 R_386_PC32        00000000   puts
    
    Relocation section '.rel.eh_frame' at offset 0x1ac contains 1 entries:
     Offset     Info    Type            Sym.Value  Sym. Name
    00000020  00000202 R_386_PC32        00000000   .text
    
    The decoding of unwind sections for machine type Intel 80386 is not currently supported.
    
    Symbol table '.symtab' contains 11 entries:
       Num:    Value  Size Type    Bind   Vis      Ndx Name
         0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
         1: 00000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
         2: 00000000     0 SECTION LOCAL  DEFAULT    1 
         3: 00000000     0 SECTION LOCAL  DEFAULT    3 
         4: 00000000     0 SECTION LOCAL  DEFAULT    4 
         5: 00000000     0 SECTION LOCAL  DEFAULT    5 
         6: 00000000     0 SECTION LOCAL  DEFAULT    7 
         7: 00000000     0 SECTION LOCAL  DEFAULT    8 
         8: 00000000     0 SECTION LOCAL  DEFAULT    6 
         9: 00000000    46 FUNC    GLOBAL DEFAULT    1 main
        10: 00000000     0 NOTYPE  GLOBAL DEFAULT  UND puts
    
    No version information found in this file.

## 用 readelf -a hello 查看可执行文件

    $ readelf -a hello
    
    ELF Header:
      Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
      Class:                             ELF32
      Data:                              2's complement, little endian
      Version:                           1 (current)
      OS/ABI:                            UNIX - System V
      ABI Version:                       0
      Type:                              EXEC (Executable file)
      Machine:                           Intel 80386
      Version:                           0x1
      Entry point address:               0x8048310
      Start of program headers:          52 (bytes into file)
      Start of section headers:          5984 (bytes into file)
      Flags:                             0x0
      Size of this header:               52 (bytes)
      Size of program headers:           32 (bytes)
      Number of program headers:         9
      Size of section headers:           40 (bytes)
      Number of section headers:         30
      Section header string table index: 27
    
    Section Headers:
      [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
      [ 0]                   NULL            00000000 000000 000000 00      0   0  0
      [ 1] .interp           PROGBITS        08048154 000154 000013 00   A  0   0  1
      [ 2] .note.ABI-tag     NOTE            08048168 000168 000020 00   A  0   0  4
      [ 3] .note.gnu.build-i NOTE            08048188 000188 000024 00   A  0   0  4
      [ 4] .gnu.hash         GNU_HASH        080481ac 0001ac 000020 04   A  5   0  4
      [ 5] .dynsym           DYNSYM          080481cc 0001cc 000050 10   A  6   1  4
      [ 6] .dynstr           STRTAB          0804821c 00021c 00004a 00   A  0   0  1
      [ 7] .gnu.version      VERSYM          08048266 000266 00000a 02   A  5   0  2
      [ 8] .gnu.version_r    VERNEED         08048270 000270 000020 00   A  6   1  4
      [ 9] .rel.dyn          REL             08048290 000290 000008 08   A  5   0  4
      [10] .rel.plt          REL             08048298 000298 000010 08  AI  5  23  4
      [11] .init             PROGBITS        080482a8 0002a8 000023 00  AX  0   0  4
      [12] .plt              PROGBITS        080482d0 0002d0 000030 04  AX  0   0 16
      [13] .plt.got          PROGBITS        08048300 000300 000008 00  AX  0   0  8
      [14] .text             PROGBITS        08048310 000310 000182 00  AX  0   0 16
      [15] .fini             PROGBITS        08048494 000494 000014 00  AX  0   0  4
      [16] .rodata           PROGBITS        080484a8 0004a8 00000e 00   A  0   0  4
      [17] .eh_frame_hdr     PROGBITS        080484b8 0004b8 00002c 00   A  0   0  4
      [18] .eh_frame         PROGBITS        080484e4 0004e4 0000cc 00   A  0   0  4
      [19] .init_array       INIT_ARRAY      08049f0c 000f0c 000004 00  WA  0   0  4
      [20] .fini_array       FINI_ARRAY      08049f10 000f10 000004 00  WA  0   0  4
      [21] .dynamic          DYNAMIC         08049f14 000f14 0000e8 08  WA  6   0  4
      [22] .got              PROGBITS        08049ffc 000ffc 000004 04  WA  0   0  4
      [23] .got.plt          PROGBITS        0804a000 001000 000014 04  WA  0   0  4
      [24] .data             PROGBITS        0804a014 001014 000008 00  WA  0   0  4
      [25] .bss              NOBITS          0804a01c 00101c 000004 00  WA  0   0  1
      [26] .comment          PROGBITS        00000000 00101c 00002a 01  MS  0   0  1
      [27] .shstrtab         STRTAB          00000000 001658 000105 00      0   0  1
      [28] .symtab           SYMTAB          00000000 001048 000410 10     29  44  4
      [29] .strtab           STRTAB          00000000 001458 000200 00      0   0  1
    Key to Flags:
      W (write), A (alloc), X (execute), M (merge), S (strings)
      I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
      O (extra OS processing required) o (OS specific), p (processor specific)
    
    There are no section groups in this file.
    
    Program Headers:
      Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
      PHDR           0x000034 0x08048034 0x08048034 0x00120 0x00120 R E 0x4
      INTERP         0x000154 0x08048154 0x08048154 0x00013 0x00013 R   0x1
          [Requesting program interpreter: /lib/ld-linux.so.2]
      LOAD           0x000000 0x08048000 0x08048000 0x005b0 0x005b0 R E 0x1000
      LOAD           0x000f0c 0x08049f0c 0x08049f0c 0x00110 0x00114 RW  0x1000
      DYNAMIC        0x000f14 0x08049f14 0x08049f14 0x000e8 0x000e8 RW  0x4
      NOTE           0x000168 0x08048168 0x08048168 0x00044 0x00044 R   0x4
      GNU_EH_FRAME   0x0004b8 0x080484b8 0x080484b8 0x0002c 0x0002c R   0x4
      GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RW  0x10
      GNU_RELRO      0x000f0c 0x08049f0c 0x08049f0c 0x000f4 0x000f4 R   0x1
    
     Section to Segment mapping:
      Segment Sections...
       00     
       01     .interp 
       02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rel.dyn .rel.plt .init .plt .plt.got .text .fini .rodata .eh_frame_hdr .eh_frame 
       03     .init_array .fini_array .dynamic .got .got.plt .data .bss 
       04     .dynamic 
       05     .note.ABI-tag .note.gnu.build-id 
       06     .eh_frame_hdr 
       07     
       08     .init_array .fini_array .dynamic .got 
    
    Dynamic section at offset 0xf14 contains 24 entries:
      Tag        Type                         Name/Value
     0x00000001 (NEEDED)                     Shared library: [libc.so.6]
     0x0000000c (INIT)                       0x80482a8
     0x0000000d (FINI)                       0x8048494
     0x00000019 (INIT_ARRAY)                 0x8049f0c
     0x0000001b (INIT_ARRAYSZ)               4 (bytes)
     0x0000001a (FINI_ARRAY)                 0x8049f10
     0x0000001c (FINI_ARRAYSZ)               4 (bytes)
     0x6ffffef5 (GNU_HASH)                   0x80481ac
     0x00000005 (STRTAB)                     0x804821c
     0x00000006 (SYMTAB)                     0x80481cc
     0x0000000a (STRSZ)                      74 (bytes)
     0x0000000b (SYMENT)                     16 (bytes)
     0x00000015 (DEBUG)                      0x0
     0x00000003 (PLTGOT)                     0x804a000
     0x00000002 (PLTRELSZ)                   16 (bytes)
     0x00000014 (PLTREL)                     REL
     0x00000017 (JMPREL)                     0x8048298
     0x00000011 (REL)                        0x8048290
     0x00000012 (RELSZ)                      8 (bytes)
     0x00000013 (RELENT)                     8 (bytes)
     0x6ffffffe (VERNEED)                    0x8048270
     0x6fffffff (VERNEEDNUM)                 1
     0x6ffffff0 (VERSYM)                     0x8048266
     0x00000000 (NULL)                       0x0
    
    Relocation section '.rel.dyn' at offset 0x290 contains 1 entries:
     Offset     Info    Type            Sym.Value  Sym. Name
    08049ffc  00000206 R_386_GLOB_DAT    00000000   __gmon_start__
    
    Relocation section '.rel.plt' at offset 0x298 contains 2 entries:
     Offset     Info    Type            Sym.Value  Sym. Name
    0804a00c  00000107 R_386_JUMP_SLOT   00000000   puts@GLIBC_2.0
    0804a010  00000307 R_386_JUMP_SLOT   00000000   __libc_start_main@GLIBC_2.0
    
    The decoding of unwind sections for machine type Intel 80386 is not currently supported.
    
    Symbol table '.dynsym' contains 5 entries:
       Num:    Value  Size Type    Bind   Vis      Ndx Name
         0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
         1: 00000000     0 FUNC    GLOBAL DEFAULT  UND puts@GLIBC_2.0 (2)
         2: 00000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
         3: 00000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.0 (2)
         4: 080484ac     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used
    
    Symbol table '.symtab' contains 65 entries:
       Num:    Value  Size Type    Bind   Vis      Ndx Name
         0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
         1: 08048154     0 SECTION LOCAL  DEFAULT    1 
         2: 08048168     0 SECTION LOCAL  DEFAULT    2 
         3: 08048188     0 SECTION LOCAL  DEFAULT    3 
         4: 080481ac     0 SECTION LOCAL  DEFAULT    4 
         5: 080481cc     0 SECTION LOCAL  DEFAULT    5 
         6: 0804821c     0 SECTION LOCAL  DEFAULT    6 
         7: 08048266     0 SECTION LOCAL  DEFAULT    7 
         8: 08048270     0 SECTION LOCAL  DEFAULT    8 
         9: 08048290     0 SECTION LOCAL  DEFAULT    9 
        10: 08048298     0 SECTION LOCAL  DEFAULT   10 
        11: 080482a8     0 SECTION LOCAL  DEFAULT   11 
        12: 080482d0     0 SECTION LOCAL  DEFAULT   12 
        13: 08048300     0 SECTION LOCAL  DEFAULT   13 
        14: 08048310     0 SECTION LOCAL  DEFAULT   14 
        15: 08048494     0 SECTION LOCAL  DEFAULT   15 
        16: 080484a8     0 SECTION LOCAL  DEFAULT   16 
        17: 080484b8     0 SECTION LOCAL  DEFAULT   17 
        18: 080484e4     0 SECTION LOCAL  DEFAULT   18 
        19: 08049f0c     0 SECTION LOCAL  DEFAULT   19 
        20: 08049f10     0 SECTION LOCAL  DEFAULT   20 
        21: 08049f14     0 SECTION LOCAL  DEFAULT   21 
        22: 08049ffc     0 SECTION LOCAL  DEFAULT   22 
        23: 0804a000     0 SECTION LOCAL  DEFAULT   23 
        24: 0804a014     0 SECTION LOCAL  DEFAULT   24 
        25: 0804a01c     0 SECTION LOCAL  DEFAULT   25 
        26: 00000000     0 SECTION LOCAL  DEFAULT   26 
        27: 00000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
        28: 08048350     0 FUNC    LOCAL  DEFAULT   14 deregister_tm_clones
        29: 08048390     0 FUNC    LOCAL  DEFAULT   14 register_tm_clones
        30: 080483d0     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux
        31: 0804a01c     1 OBJECT  LOCAL  DEFAULT   25 completed.7493
        32: 08049f10     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtors_aux_fin
        33: 08048400     0 FUNC    LOCAL  DEFAULT   14 frame_dummy
        34: 08049f0c     0 OBJECT  LOCAL  DEFAULT   19 __frame_dummy_init_array_
        35: 00000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
        36: 00000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
        37: 080485ac     0 OBJECT  LOCAL  DEFAULT   18 __FRAME_END__
        38: 00000000     0 FILE    LOCAL  DEFAULT  ABS 
        39: 08049f10     0 NOTYPE  LOCAL  DEFAULT   19 __init_array_end
        40: 08049f14     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC
        41: 08049f0c     0 NOTYPE  LOCAL  DEFAULT   19 __init_array_start
        42: 080484b8     0 NOTYPE  LOCAL  DEFAULT   17 __GNU_EH_FRAME_HDR
        43: 0804a000     0 OBJECT  LOCAL  DEFAULT   23 _GLOBAL_OFFSET_TABLE_
        44: 08048490     2 FUNC    GLOBAL DEFAULT   14 __libc_csu_fini
        45: 00000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
        46: 08048340     4 FUNC    GLOBAL HIDDEN    14 __x86.get_pc_thunk.bx
        47: 0804a014     0 NOTYPE  WEAK   DEFAULT   24 data_start
        48: 0804a01c     0 NOTYPE  GLOBAL DEFAULT   24 _edata
        49: 08048494     0 FUNC    GLOBAL DEFAULT   15 _fini
        50: 0804a014     0 NOTYPE  GLOBAL DEFAULT   24 __data_start
        51: 00000000     0 FUNC    GLOBAL DEFAULT  UND puts@@GLIBC_2.0
        52: 00000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
        53: 0804a018     0 OBJECT  GLOBAL HIDDEN    24 __dso_handle
        54: 080484ac     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used
        55: 00000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_
        56: 08048430    93 FUNC    GLOBAL DEFAULT   14 __libc_csu_init
        57: 0804a020     0 NOTYPE  GLOBAL DEFAULT   25 _end
        58: 08048310     0 FUNC    GLOBAL DEFAULT   14 _start
        59: 080484a8     4 OBJECT  GLOBAL DEFAULT   16 _fp_hw
        60: 0804a01c     0 NOTYPE  GLOBAL DEFAULT   25 __bss_start
        61: 08048402    46 FUNC    GLOBAL DEFAULT   14 main
        62: 0804a01c     0 OBJECT  GLOBAL HIDDEN    24 __TMC_END__
        63: 00000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
        64: 080482a8     0 FUNC    GLOBAL DEFAULT   11 _init
    
    Histogram for `.gnu.hash' bucket list length (total of 2 buckets):
     Length  Number     % of total  Coverage
          0  1          ( 50.0%)
          1  1          ( 50.0%)    100.0%
    
    Version symbols section '.gnu.version' contains 5 entries:
     Addr: 0000000008048266  Offset: 0x000266  Link: 5 (.dynsym)
      000:   0 (*local*)       2 (GLIBC_2.0)     0 (*local*)       2 (GLIBC_2.0)  
      004:   1 (*global*)   
    
    Version needs section '.gnu.version_r' contains 1 entries:
     Addr: 0x0000000008048270  Offset: 0x000270  Link: 6 (.dynstr)
      000000: Version: 1  File: libc.so.6  Cnt: 1
      0x0010:   Name: GLIBC_2.0  Flags: none  Version: 2
    
    Displaying notes found at file offset 0x00000168 with length 0x00000020:
      Owner                 Data size	Description
      GNU                  0x00000010	NT_GNU_ABI_TAG (ABI version tag)
        OS: Linux, ABI: 2.6.32
    
    Displaying notes found at file offset 0x00000188 with length 0x00000024:
      Owner                 Data size	Description
      GNU                  0x00000014	NT_GNU_BUILD_ID (unique build ID bitstring)
        Build ID: 5085f7128206d2cbc7f72a6b4d42aed8b8ea29bc


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
