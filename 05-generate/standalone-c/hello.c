#include <unistd.h>
#include <stdio.h>

#ifdef CUSTOM
void _start(void)
#else
int main(void)
#endif
{
	printf("hello\n");

	_exit(0);
#ifndef CUSTOM
	return 0;
#endif
}
