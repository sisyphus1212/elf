

1. default libraries search path

    /etc/ld.so.conf: /lib32/

2. puts/exit in libc.so

    $ readelf -s /lib32/libc.so.6 | egrep " puts@| exit@"
    150: 00037f80    39 FUNC    GLOBAL DEFAULT   16 exit@@GLIBC_2.0
    461: 00071290   531 FUNC    WEAK   DEFAULT   16 puts@@GLIBC_2.0

3. load info of libc.so.6

    $ readelf -l /lib32/libc.so.6 | grep LOAD
    LOAD           0x000000 0x00000000 0x00000000 0x1c184 0x1c184 R   0x1000
    LOAD           0x01d000 0x0001d000 0x0001d000 0x157c73 0x157c73 R E 0x1000
    LOAD           0x175000 0x00175000 0x00175000 0x6f911 0x6f911 R   0x1000
    LOAD           0x1e4a6c 0x001e5a6c 0x001e5a6c 0x02c8c 0x054a0 RW  0x1000

4. symbol and addr info

    $  objdump -d /lib32/libc.so.6 | egrep "_puts@@.*>:|exit@@.*>:"
    00037f80 <exit@@GLIBC_2.0>:
    00037fb0 <on_exit@@GLIBC_2.0>:
    00038300 <__cxa_atexit@@GLIBC_2.1.3>:
    00038590 <quick_exit@@GLIBC_2.24>:
    000385c0 <__cxa_at_quick_exit@@GLIBC_2.10>:
    00071290 <_IO_puts@@GLIBC_2.0>:
    000809b0 <pthread_exit@@GLIBC_2.0>:
    000cc166 <_exit@@GLIBC_2.0>:
    0013ac80 <svc_exit@@GLIBC_2.0>:

