#include <stdio.h>

#ifdef FUNC_CALL_ATTR
/* available: cdecl, fastcall */
__attribute__((FUNC_CALL_ATTR))
#endif
int func(int arg1, int arg2, int arg3)
{
	int i, j, k, total;

	i = arg1;
	j = arg2;
	k = arg3;

	total = i + j + k;
	printf("total = %d\n", total);

	return total;
}

/* int main(int argc, char *argv[]) */
int main(void)
{
	int ret;

	ret = func(1, 3, 5);

	printf("func return %d\n", ret);

	return 0;
}
