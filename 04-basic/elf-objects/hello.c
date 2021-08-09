#include <stdio.h>

#ifdef SHARED_EXEC_MANUAL
/* For executable shared objects with -shared -pic -Wl,-e,main; not required for -pie -Wl,-E */

#include <unistd.h>
//const char service_interp[] __attribute__((section(".interp"))) = "/lib32/ld-linux.so.2";

asm(".section .interp,\"a\"\n"
   "        .string \"/lib32/ld-linux.so.2\"\n");
#endif

int main(int argc, char *argv[])
{
	printf("hello\n");

#ifdef SHARED_EXEC_MANUAL
	_exit(0);
#endif

	return 0;
}
