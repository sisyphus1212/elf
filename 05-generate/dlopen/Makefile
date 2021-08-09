
all: libmyprintf.so test-autoload test-dlopen run

run: test-autoload test-dlopen

libmyprintf.so: myprintf.c
	gcc -m32 -c $<
	gcc -m32 -shared -Wl,-soname,libmyprintf.so.0 -o libmyprintf.so.0.0 myprintf.o
	ln -sf libmyprintf.so.0.0 libmyprintf.so.0
	ln -fs libmyprintf.so.0 libmyprintf.so

test-autoload: test-autoload.c libmyprintf.so
	gcc -m32 -o $@ $< -lmyprintf -L./ -I./ 
	LD_LIBRARY_PATH=./ ldd $@
	LD_LIBRARY_PATH=./ ./test-autoload
	LD_BIND_NOW=1 LD_LIBRARY_PATH=./ ./test-autoload

test-dlopen: test-dlopen.c libmyprintf.so
	gcc -m32 -o $@ $< -ldl
	LD_LIBRARY_PATH=./ ldd $@
	./test-dlopen

clean:
	rm -rf test-autoload test-dlopen libmyprintf.so* *.o
