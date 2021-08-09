#include <stdio.h>

#ifdef OVERFLOW_TEST
void overflow_test(void)
{
	char a[3];

	a[3] = '5';
	a[10] = '5';
	a[50] = 'f';
	a[-3] = 'f';
}
#endif

#ifdef SEGFAULT_TEST
void segfault_test(void)
{
	int i = 0;

	printf("Please input a number: ");
	scanf("%d", i);
}
#endif


int main(int argc, char *argv[])
{
#ifdef OVERFLOW_TEST
	overflow_test();
#endif

#ifdef SEGFAULT_TEST
	segfault_test();
#endif

	printf("hello\n");

	return 0;
}
