
# Process context: parameters and environments

## Shell version

    $ ./test.sh arg1 arg2
    args:
         ./test.sh   
    env:
         /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:...

## C version

    $ make
    cc -m32 -g -o test test.c
    ./test
    envp[0]: PAPERSIZE=a4
    getenv("PATH"): /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:...
    environ[0]: PAPERSIZE=a4

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
