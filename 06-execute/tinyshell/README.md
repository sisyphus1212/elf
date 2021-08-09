
# Wring a tiny shell

该 Shell 可以执行命令，并支持管道。

在源代码基础上做了几处修订：

* 替换 gets 为 fgets
* 替换 strcmp 为 strncmp，并增加缺失的头文件
* 修订结束命令的判断，需要加一个换行，否则匹配不到
* 在 `tinysh >>` 前打印空行；在读取到命令后打印空行

## 使用

    $ make

    tiny sh>> ls | grep tinysh

    tinysh
    tinysh.c

    tiny sh>> quit


---
Copyright belongs to tinyshell's author and Wu Zhangin, Wechat: tinylab
<http://tinylab.org/360-elf>
