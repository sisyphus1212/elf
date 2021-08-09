
# Using shared libraries explicitly or implicitly

## Implicitly

    $ make test-autoload
    gcc -m32 -c myprintf.c
    gcc -m32 -shared -Wl,-soname,libmyprintf.so.0 -o libmyprintf.so.0.0 myprintf.o
    ln -sf libmyprintf.so.0.0 libmyprintf.so.0
    ln -fs libmyprintf.so.0 libmyprintf.so
    gcc -m32 -o test-autoload test-autoload.c -lmyprintf -L./ -I./
    LD_LIBRARY_PATH=./ ldd test-autoload
    	linux-gate.so.1 =>  (0xf7737000)
    	libmyprintf.so.0 => ./libmyprintf.so.0 (0xf7730000)
    	libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xf7552000)
    	/lib/ld-linux.so.2 (0xf7738000)
    LD_LIBRARY_PATH=./ ./test-autoload
    Hello World
    LD_BIND_NOW=1 LD_LIBRARY_PATH=./ ./test-autoload
    Hello World

## Explicitly

    $ make test-dlopen
    gcc -m32 -o test-dlopen test-dlopen.c -ldl
    LD_LIBRARY_PATH=./ ldd test-dlopen
	linux-gate.so.1 =>  (0xf77c3000)
	libdl.so.2 => /lib/i386-linux-gnu/libdl.so.2 (0xf7792000)
	libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xf75dc000)
	/lib/ld-linux.so.2 (0xf77c4000)
    ./test-dlopen
    Hello World
