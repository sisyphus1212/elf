shell echo -e '\nlist source code\n'
l
l
shell echo -e '\nset breakpoints\n'

shell echo -e '\nset at _start\n'
b 9

shell echo -e '\nset at puts@plt\n'
b *0x08048170

shell echo -e '\nset after call puts@plt\n'
b 14

shell echo -e '\nset at plt0\n'
b *0x08048150

shell echo -e '\nset at puts -->  not real puts here, still puts@plt\n'
b puts
p puts

shell echo -e '\nrunning the program\n'
r

shell echo -e '\nchecking value of GOT4, should be real puts for LD_BIND_NOW=1 \n'
x 0x80481c8

shell echo -e '\nchecking value of GOT3\n'
x 0x80481c4

shell echo -e '\nchecking value of GOT2, should be 0 for LD_BIND_NOW=1 \n'
x 0x80481c0

shell echo -e '\nchecking value of GOT1, should be 0 for LD_BIND_NOW=1 \n'
x 0x80481bc

shell echo -e '\nchecking value of GOT0\n'
x 0x80481b8


shell echo -e '\ndisassemble puts@plt\n'
disassemble 0x08048170

shell echo -e '\nchecking value of GOT4, should be real puts for LD_BIND_NOW=1 \n'
x 0x80481c8

shell echo -e '\nchecking value of GOT3\n'
x 0x80481c4

shell echo -e '\nchecking value of GOT2, should be 0 for LD_BIND_NOW=1 \n'
x 0x80481c0

shell echo -e '\nchecking value of GOT1, should be 0 for LD_BIND_NOW=1 \n'
x 0x80481bc

shell echo -e '\nchecking value of GOT0\n'
x 0x80481b8

shell echo -e '\ncontinue running...\n'
c

shell echo -e '\nrunning one by one with si ...\n'
si
si
si

shell echo -e '\nchecking GOT4 again, is it the real puts address...\n'
x 0x80481c8

shell echo -e '\nrunning one by one with si ...\n'
si
si
si
si

shell echo -e '\nchecking GOT4 again, is it the real puts address...\n'
x 0x80481c8

shell echo -e '\ncontinue running ...\n'
c

shell echo -e '\nchecking GOT4 again, is it the real puts address...\n'
x 0x80481c8

shell echo -e '\nprint puts address\n'
b puts
p puts

shell echo -e '\ncontinue running ... '
d
c
quit
