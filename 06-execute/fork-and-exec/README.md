

# Creating new process

## fork+exec

    $ make fork-execlp
    cc -o fork-execlp fork-execlp.c
    ./fork-execlp
    [PARENT]: pid is 41341
    [CHILD]: pid is 41342
    [CHILD]: parent's pid is 41341
    [PARENT]: wait for my child exit successfully!

## clone

    $ make clone
    cc -o clone clone.c
    ./clone
    [PARENT] creating son thread!
    [CHILD] pid: 41350, val: 20
    [PARENT] pid: 41349, val: 5

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
