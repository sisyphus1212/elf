
all:
	gcc -m32 -shared -fpic -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-stack-protector -S hello.c
	gcc -m32 -shared -fpic -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-stack-protector -c -o hello.o hello.s
	gcc -m32 -shared -fpic -o libhello.so hello.o
	gcc -m32 -o main main.c -L./ -lhello
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./ ./main
	objdump -d -j .text libhello.so | grep -A 14 "<hello>:"

new:
	gcc -m32 -g -shared -fpic -o libhello.so hello.new.s
	gcc -m32 -o main main.c -L./ -lhello
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./ ./main
	objdump -d -j .text libhello.so | grep -A 14 "<hello>:"

clean:
	rm -f libhello.so hello.o hello.s main
