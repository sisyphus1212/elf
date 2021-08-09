
all: inline attribute objcopy

inline:
	gcc -m32 -shared -fpic -o libhello-inline-asm.so inline-asm.c
	./libhello-inline-asm.so

attribute:
	gcc -m32 -shared -fpic -o libhello-c-attribute.so c-attribute.c
	./libhello-c-attribute.so

objcopy:
	#gcc -m32 -shared -fpic -c -o dummy.o dummy.c
	#objcopy --add-section .interp=interp.txt dummy.o --set-section-flags .interp=alloc,readonly
	#gcc -m32 -shared -fpic -o libhello-objcopy.so objcopy.c dummy.o #-Tld.script
	bash -c 'echo -en "/lib32/ld-linux.so.2\x00" > interp.section.txt'
	gcc -m32 -shared -fpic -c -o objcopy.o objcopy.c
	objcopy --add-section .interp=interp.section.txt objcopy.o --set-section-flags .interp=alloc,readonly
	gcc -m32 -shared -fpic -o libhello-objcopy.so objcopy.o #-Tld.script
	./libhello-objcopy.so

update: attribute
	objcopy --dump-section .interp=interp.txt libhello-c-attribute.so
	sed -i -e "s%/lib32/ld-linux.so.2%$(shell ls /lib32/ld-2*.so)%g" interp.txt
	objcopy --update-section .interp=interp.txt libhello-c-attribute.so
	chmod a+x libhello-c-attribute.so
	./libhello-c-attribute.so

clean:
	rm -rf ./libhello-inline-asm.so ./libhello-c-attribute.so ./libhello-objcopy.so dummy.o objcopy.o core interp.txt libhello.so hello.o
