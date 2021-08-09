
# Pure assembly code

## ret.s

A pure assembly code only return a status, which only has `_start` and `sys_exit` call.

    $ make ret
    as --32 -o ret.o ret.s
    ld -m elf_i386 -o ret ret.o
    wc -c ret
    452 ret
    strip -s ret
    wc -c ret
    236 ret
    dd if=ret of=ret.strip bs=1 count=$((0x$(readelf -S ret | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
    96+0 records in
    96+0 records out
    96 bytes copied, 0.000283106 s, 339 kB/s
    mv ret.strip ret
    chmod +x ret
    wc -c ret
    96 ret
    ./ret ; echo $?
    42

## x86-hello.s

A pure assembly code with both of print and exit support:

    $ make x86-hello
    as --32 -o x86-hello.o x86-hello.s
    ld -m elf_i386 -o x86-hello x86-hello.o
    wc -c x86-hello
    616 x86-hello
    strip -s x86-hello
    wc -c x86-hello
    312 x86-hello
    dd if=x86-hello of=x86-hello.strip bs=1 count=$((0x$(readelf -S x86-hello | grep .shstrtab | tr -s ' ' | sed -e "s/\[ */\[/g" | cut -d' ' -f6)))
    125+0 records in
    125+0 records out
    125 bytes copied, 0.000295405 s, 423 kB/s
    mv x86-hello.strip x86-hello
    chmod +x x86-hello
    wc -c x86-hello
    125 x86-hello
    ./x86-hello ; echo $?
    hello
    0

## With our own ld.script

    $ make ret LD_SCRIPT=y

## Without strip

    $ make ret STRIP=n
    as --32 -o ret.o ret.s
    ld -m elf_i386 -o ret ret.o
    ./ret ; echo $?
    42
    $ wc -c ret
    452 ret
    
