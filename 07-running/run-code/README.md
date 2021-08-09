
# code running methods

这里介绍了十多种执行 Linux C 语言或汇编语言代码的方式，透彻理解程序运行和开发必读。

* exec, 直接执行代码
* shlib, 当共享库使用+直接执行共享库
* dlopen，通过 dlopen 直接解析代码符号并运行
* cscript，以脚本的方式运行 C 语言程序
* emulator，通过模拟器运行 C 语言程序
* binfmtc-extension，通过扩展名直接运行
* binfmtc-magic，自定义一个魔数直接运行
* embed-ldscript，把代码嵌入到另外一个程序运行，用 ldscript 辅助
* embed-objcopy，把代码嵌入到另外一个程序运行，用 objcopy 辅助
* embed-pic，把代码嵌入到另外一个程序运行，代码本身实现位置无关
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
