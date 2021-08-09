
SRC := hello.c print.c print.h

hello: $(SRC)
		gcc -m32 -o $@ $^
		./$@

clean:
		rm -rf hello
