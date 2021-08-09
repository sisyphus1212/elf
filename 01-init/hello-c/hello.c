#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef SEGFAULT_TEST
	int i = 0;

	printf("Please input a number: ");
	scanf("%d", i);
#endif

	printf("hello\n");

	return 0;
}
