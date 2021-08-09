/* refs: (linux)/include/linux/compiler-gcc.h */

#include <stdio.h>

#define GCC_VERSION (__GNUC__ * 10000           \
                     + __GNUC_MINOR__ * 100     \
                     + __GNUC_PATCHLEVEL__)

#if GCC_VERSION < 30200
# error Sorry, your compiler is too old - please upgrade it.
#endif

#ifdef OTHER_ERROR
int main(int argc)
#else
int main(void)
/* int main(int argc, char *argv[]) */
#endif
{
	printf("Gcc version is %d\n", GCC_VERSION);

#ifdef STD_ERROR
	/*return 0;*/
#else	
	return 0;
#endif
}
