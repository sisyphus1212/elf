
# Using tcc

## 安装

    $ sudo apt-get install tcc

## 试用

    // 编译后运行（实际 size 数值可能会因 tcc 版本不同而有一定差异）
    $ make
    tcc -o hello hello.c
    size hello
       text	   data	    bss	    dec	    hex	filename
        818	    227	      0	   1045	    415	hello
    wc -c hello
    3456 hello

    // 直接运行
    $ make run
    tcc -run hello.c
    hello

## 查看 ELF 信息

    $ make readelf


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
