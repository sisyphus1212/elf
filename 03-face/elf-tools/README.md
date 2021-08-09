
# elf tools usage

该节介绍了多种 ELF 工具，包括 readelf/eu-readelf, objdump, objcopy, 还介绍了 dd 命令。

请参考幻灯片和下文进行进行实验。

`eu-readelf` 需要先安装 elfutils，这个工具是 binutils 的补充和增强:

    $ sudo apt-get -y update
    $ sudo apt-get install -y elfutils

## 用法演示

    // 编译
    $ make

    // 查看各个 header 与 table
    $ make eh sht pht

    // 查看各个节区
    $ make symtab strtab dynsym dynamic relocs eh_frame note version

    // dump 出某个节区的 string or hex
    $ make hex S=.strtab
    $ make string S=.strtab

    // 反汇编代码部分
    $ make disasm S=.init

    // 裁剪不同部分

    // 裁剪 .symtab, .strtab
    $ make strip
    // 删除指定节区
    $ make strip-section S=.comment
    // 删除所有不影响执行的节区
    $ make strip-sections
    // 删除节区头表和节区名字符串表
    $ make strip-nonexec
    // 删除所有能删除
    $ make strip-all

    // 设置 GNU* 相关段为空段
    $ make null-gnu-segments

    // 把程序头表中的未用到的 paddr 部分全部清空
    $ make null-pht-paddrs

## 查看并统计 Sections

Section Header Table 用于描述各个 Sections 的信息，用 `readelf -S hello` 可以查看。

    $ make sort-sections


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
