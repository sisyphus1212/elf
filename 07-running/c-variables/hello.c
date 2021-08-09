/* Author: Wu Zhangjin, Wechat: tinylab */

#include <stdio.h>

static int m;
static int n = 1000;
int a;
int b = 10000;

static int hello(void)
{
	static int i;
	static int j = 10;
	int x;
	int y = 100;
	register int z = 33;

	printf("i = %d, addr of i = %p\n", i, &i);
	printf("j = %d, addr of j = %p\n", j, &j);
	printf("x = %d, addr of x = %p\n", x, &x);
	printf("y = %d, addr of y = %p\n", y, &y);
	printf("z = %d, in register, no addr\n", z);

	return 0;
}

int main(int argc, char *argv[])
{
	printf("argc = %d, addr of argc = %p\n", argc, &argc);
	printf("argv = %s, addr of argv = %p\n", argv[0], argv);
	printf("m = %d, addr of m = %p\n", m, &m);
	printf("n = %d, addr of n = %p\n", n, &n);
	printf("a = %d, addr of a = %p\n", a, &a);
	printf("b = %d, addr of b = %p\n", b, &b);

	hello();

	return 0;
}
