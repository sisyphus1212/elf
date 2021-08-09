/*
 * monitor.c
 *
 * Author: Wuzhangjin, Wechat: tinylab
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include <openssl/md5.h>
#include <errno.h>

int main_end();
extern char __executable_start, __etext;

/* from: https://blog.csdn.net/legnyu880412/article/details/72841277 */
unsigned short checksum(char *addr, int count)
{
	register int sum = 0;

	while (count > 1) 
	{
		sum = sum+*(unsigned short*)addr;
		addr+= 2;
		count -= 2;
	}

	if ( count > 0 ) // =1,说明count为奇数
	sum += *addr;

	while (sum>>16) //当和的高16位不为0，把高16位作为校验和的一部分求和，
	sum = (sum & 0xffff) + (sum >> 16);

	return (short)~sum;
}

int _checksum(char *start, char *end)
{
	return checksum(start, end - start);
}

int main(int argc, char *argv[])
{
	int cs;
	int base;
	char *endptr, *str;
	long val;

	if (argc < 2) {
	    fprintf(stderr, "Usage: %s checksum\n", argv[0]);
	    exit(EXIT_FAILURE);
	}

	str = argv[1];
	base = (argc > 2) ? atoi(argv[2]) : 10;

	errno = 0;    /* To distinguish success/failure after call */
	val = strtol(str, &endptr, base);

	cs = _checksum((char *)&main, (char *)&main_end);
	//cs = checksum(&__executable_start, &__etext);

	printf("checksum is %d\n", cs);
	if (cs != val)
		printf("who touched me!\n");
	else
		printf("I'm good...\n");

	return 0;
}

int main_end()
{
	printf("__main_end__\n");
}
