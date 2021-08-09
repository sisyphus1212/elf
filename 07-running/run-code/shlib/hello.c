/* Author: Wu Zhangjin, Wechat: tinylab */

#include <stdio.h>

#ifdef EXEC_SHLIB
#include <unistd.h>

asm(".pushsection .interp,\"a\"\n"
    "        .string \"/lib32/ld-linux.so.2\"\n"
    ".popsection");

int entry(void)
{
	printf("%s %d: %s(): the real entry of shared library here.\n", __FILE__, __LINE__, __func__);

	/* do whatever */

	return 0;
}

int main(void)
{
	return entry();

	return 0;
}

void _start(void)
{
	int ret;

	ret = main();
	_exit(ret);
}
#else
int main(void)
{
	printf("hello\n");
	return 0;
}
#endif

void hello(void)
{
	printf("hello...\n");
}
