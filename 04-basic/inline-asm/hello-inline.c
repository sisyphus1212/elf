#include <stdio.h>

typedef unsigned long (* func_t)();

/*
 * objdump -d hello-inline
 *
 * 08048402 <get_eip>:
 * 8048402:       83 ec 10                sub    $0x10,%esp   --> esp decrease 0x10
 * 8048405:       c7 44 24 0c 00 00 00    movl   $0x0,0xc(%esp)
 *
 *
 * 8048441:       e8 bc ff ff ff          call   8048402 <get_eip>
 * 8048446:       83 ec 08                sub    $0x8,%esp
 *
 * get_eip should return 0x8048446
 */


func_t get_eip()
{
	func_t eip = 0;

	asm ("movl 0x10(%%esp), %0" : "=a" (eip) : "0" (eip));

	return eip;
}

int main(void)
{
        int i = 5;
        int j = 0;

	printf("eip of next inst of call get_eip() is 0x10(%%esp): %p\n", (func_t)get_eip());

	printf("before call inline asm: i = %d, j = %d\n", i, j);

	asm volatile ("incl %0\n"              /* i = i+1 */
		      "movl %0, %1\n"          /* j = i */
		     :"=a"(i), "=b"(j)
		     :"0" (i), "1" (j));

	printf("after call inline asm: i = %d, j = %d\n", i, j);

	return 0;
}

