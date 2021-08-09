
# Learning big and little endian

## Prepare

    $ sudo apt-get update -y
    $ sudo apt-get install -y libc6-dev-armel-cross libc6-armel-cross
    $ sudo apt-get install -y libc6-dev-powerpc-cross libc6-powerpc-cross

## Testing

    $ make compare

    x86:

                   sizeof data is 4

                   addr      data

                   0x804a024 0x1020304

                   0x804a024 0x4
                   0x804a025 0x3
                   0x804a026 0x2
                   0x804a027 0x1

                   Little endian

    arm:

                   sizeof data is 4

                   addr      data

                   0x1102c 0x1020304

                   0x1102c 0x4
                   0x1102d 0x3
                   0x1102e 0x2
                   0x1102f 0x1

                   Little endian

    ppc:

                   sizeof data is 4

                   addr      data

                   0x1002001c 0x1020304

                   0x1002001c 0x1
                   0x1002001d 0x2
                   0x1002001e 0x3
                   0x1002001f 0x4

                   Big endian


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
