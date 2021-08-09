# mini elf loader

该章节视频课程为新增，主要介绍了如何实现一个小型的 ELF 装载器，相关代码放在 07-running/run-code/ 目录。

* load-malloc-auto，通过另外一个程序加载到使用 malloc 分配的内存后运行，动态修改地址
* load-malloc-pic，通过另外一个程序加载到使用 malloc 分配的内存后运行，使用位置无关代码
* load-mmap-auto，通过另外一个程序加载到使用 mmap 申请的内存后运行，动态修改地址
* load-mmap-fixed，通过另外一个程序加载到使用 mmap 申请的内存后运行，使用固定地址
* load-mmap-pic，通过另外一个程序加载到使用 mmap 申请的内存后运行，使用位置无关代码
* load-mmap-myelf, 设计一个极简程序格式，并撰写了一个可用于加载和运行该格式的 mini loader
* load-mmap-elf, 撰写了一个可以用于加载和运行简单 elf 程序的 mini loader

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
