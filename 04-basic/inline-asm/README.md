
# Inline Assembly Usage

    $ make
    gcc -fno-stack-protector -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-pie -no-pie -m32 -Wall -Werror  -o hello-inline hello-inline.c

    objdump -d hello-inline | grep -A1 "call.*get_eip"
     8048441:	e8 bc ff ff ff       	call   8048402 <get_eip>
     8048446:	83 ec 08             	sub    $0x8,%esp
    objdump -d hello-inline | grep -A2 "get_eip>:"
    08048402 <get_eip>:
     8048402:	83 ec 10             	sub    $0x10,%esp
     8048405:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
  
    eip of next inst of call get_eip() is 0x10(%esp): 0x8048446
    before call inline asm: i = 5, j = 0
    after call inline asm: i = 6, j = 6

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
