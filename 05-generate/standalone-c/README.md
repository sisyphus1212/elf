
# 重构一个不需要 main，不需要链接 crt*.o 的程序

* 需要一个没返回值的 _start
* 需要在末尾调用 _exit

## 初始C 代码

```
void _start(void)
{
	printf("hello\n");

	_exit(0);
}
```

    $ make
    696 hello.strip

## 试试 gcc 的 -nostartfiles

这个参数可以避免链接进来那些额外的 .o 文件，可以用 objdump 查看，确实没有链接进来。

    $ make hello.nostart
    $ objdump -d hello.nostart

## 得到的汇编代码优化：hello.s.minial

```
        .section        .rodata
.LC0:
        .string "hello"
        .text
        .globl  _start
_start:
	subl    $8, %esp   # 分配栈空间 
        pushl   $.LC0
        call    puts
        pushl   $0
        call    _exit
```

测试用，请把 hello.s.minimal 覆盖到 hello.s 中。

    $ cp hello.s.minimal hello.s

用 ld.script 重构程序头表，可参考 [PHDRS Command](https://sourceware.org/binutils/docs/ld/PHDRS.html)：

```
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SEARCH_DIR("=/usr/lib32");
PHDRS
{
  headers PT_PHDR PHDRS FLAGS (5);
  interp PT_INTERP;
  loadr PT_LOAD FILEHDR PHDRS;
  loadw PT_LOAD;
  dynamic PT_DYNAMIC;
}
SECTIONS
{
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x08048000));
  . = SEGMENT_START("text-segment", 0x08048000) + SIZEOF_HEADERS;
  .interp         : { *(.interp) } : interp : loadr
  .dynsym         : { *(.dynsym) } : loadr
  .dynstr         : { *(.dynstr) } : loadr
  .gnu.version_r  : { *(.gnu.version_r) } : loadr
  .rel.plt        : { *(.rel.plt .rel.iplt) } : loadr
  .plt            : { *(.plt) *(.iplt) } : loadr
  .text           : { *(.text*  .gnu.linkonce.t.*) } : loadr
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) } : loadr
  .dynamic        : { *(.dynamic) } : dynamic : loadw
  .got.plt        : { *(.got.plt)  *(.igot.plt) } : loadw
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.comment)}
}
```

    $ as --32 -o hello.o hello.s
    $ ld -m elf_i386 --dynamic-linker /lib/ld-linux.so.2  -o hello hello.o -lc -Tld.script
    $ wc -c hello
    1820 hello
    $ strip -s hello
    $ strip -R .gnu.version -R .hash hello
    $ wc -c hello
    1224 hello
    $ readelf -S hello | grep .shstrtab 
     [11] .shstrtab         STRTAB          00000000 00028c 00005b 00      0   0  1
    $ dd if=hello of=hello.strip bs=1 count=$((0x28c))
    $ mv hello.strip hello
    $ chmod +x hello
    $ ./hello 
    hello
    $ wc -c hello
    652 

进一步可以合并 loadw 进 loadr，再次减少 32 个字节（一个 Program Header）:

```
diff --git a/05-generate/standalone-c/ld.script b/05-generate/standalone-c/ld.script
index a13c5c8..bea8129 100644
--- a/05-generate/standalone-c/ld.script
+++ b/05-generate/standalone-c/ld.script
@@ -7,7 +7,7 @@ PHDRS
   headers PT_PHDR PHDRS FLAGS (5);
   interp PT_INTERP;
   loadr PT_LOAD FILEHDR PHDRS;
-  loadw PT_LOAD;
+  /*loadw PT_LOAD;*/
   dynamic PT_DYNAMIC;
 }
 SECTIONS
@@ -22,7 +22,7 @@ SECTIONS
   .plt            : { *(.plt) *(.iplt) } : loadr
   .text           : { *(.text*  .gnu.linkonce.t.*) } : loadr
   .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) } : loadr
-  .dynamic        : { *(.dynamic) } : dynamic : loadw
-  .got.plt        : { *(.got.plt)  *(.igot.plt) } : loadw
+  .got.plt        : { *(.got.plt)  *(.igot.plt) } : loadr /* loadw */
+  .dynamic        : { *(.dynamic) } : dynamic : loadr /* loadw */
   /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.comment)}
 }
```

甚至可以直接把 `.interp` 删掉，手动运行，得到 558：

```
diff --git a/05-generate/standalone-c/ld.script b/05-generate/standalone-c/ld.script
index bea8129..a3d4f8c 100644
--- a/05-generate/standalone-c/ld.script
+++ b/05-generate/standalone-c/ld.script
@@ -5,7 +5,7 @@ SEARCH_DIR("=/usr/lib32");
 PHDRS
 {
   headers PT_PHDR PHDRS FLAGS (5);
-  interp PT_INTERP;
+  /*interp PT_INTERP;*/
   loadr PT_LOAD FILEHDR PHDRS;
   /*loadw PT_LOAD;*/
   dynamic PT_DYNAMIC;
@@ -14,7 +14,7 @@ SECTIONS
 {
   PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x08048000));
   . = SEGMENT_START("text-segment", 0x08048000) + SIZEOF_HEADERS;
-  .interp         : { *(.interp) } : interp : loadr
+  .interp         : { *(.interp) } /* : interp */ : loadr
   .dynsym         : { *(.dynsym) } : loadr
   .dynstr         : { *(.dynstr) } : loadr
   .gnu.version_r  : { *(.gnu.version_r) } : loadr
```

    $ /lib/ld-linux.so.2 ./hello
    hello

甚至再进一步，直接把 `.interp` 节区删掉，可以得到 572 个字节：

```
diff --git a/05-generate/standalone-c/ld.script b/05-generate/standalone-c/ld.script
index bea8129..cb89af3 100644
--- a/05-generate/standalone-c/ld.script
+++ b/05-generate/standalone-c/ld.script
@@ -5,7 +5,7 @@ SEARCH_DIR("=/usr/lib32");
 PHDRS
 {
   headers PT_PHDR PHDRS FLAGS (5);
-  interp PT_INTERP;
+  /*interp PT_INTERP;*/
   loadr PT_LOAD FILEHDR PHDRS;
   /*loadw PT_LOAD;*/
   dynamic PT_DYNAMIC;
@@ -14,7 +14,7 @@ SECTIONS
 {
   PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x08048000));
   . = SEGMENT_START("text-segment", 0x08048000) + SIZEOF_HEADERS;
-  .interp         : { *(.interp) } : interp : loadr
+  /* .interp         : { *(.interp) } : interp : loadr */
   .dynsym         : { *(.dynsym) } : loadr
   .dynstr         : { *(.dynstr) } : loadr
   .gnu.version_r  : { *(.gnu.version_r) } : loadr
@@ -24,5 +24,5 @@ SECTIONS
   .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) } : loadr
   .got.plt        : { *(.got.plt)  *(.igot.plt) } : loadr /* loadw */
   .dynamic        : { *(.dynamic) } : dynamic : loadr /* loadw */
-  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.comment)}
+  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.comment) *(.interp) }
 }
```

其实 `PHDR` 段也可以删掉，得到 540 字节：`$ make NORMAL=n`

```
-  headers PT_PHDR PHDRS FLAGS (5);
+  /*headers PT_PHDR PHDRS FLAGS (5);*/
```


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
