/* Author: Wu Zhangjin, Wechat: tinylab */

#include <stdio.h>

asm (".pushsection .bin, \"ax\" \n"
     ".globl bin_entry \n"
     "bin_entry: \n"
     ".incbin \"./hello.bin\" \n"
     ".popsection"
);

extern void bin_entry();

int main(int argc, char *argv[])
{
	bin_entry();

	return 0;
}
