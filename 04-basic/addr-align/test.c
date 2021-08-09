#include <stdio.h>

struct test {
	char a;
#ifdef PADDED
	char padding;
#endif
	short b;
#ifdef PACKED
} __attribute__((packed));
#else
};
#endif

/*  Packed: misaligned access
 *
 *  assume external mem bus width is 4 bytes, little endian
 *
 *     low addr 
 *     _____
 *m[0] |    |      t[0]: char a
 *     |    |            ((char *)&b)[0]
 *     |    |            ((char *)&b)[1]
 *     |____|      t[1]: char a
 *m[1] |    |            ((char *)&b)[0]
 *     |    |            ((char *)&b)[1]
 *     |    |
 *     |____|
 *
 *    high addr
 */

/*  Padded: aligned access
 *
 *  assume external mem bus width is 4 bytes, little endian
 *
 *     low addr 
 *     _____
 *m[0] |    |      t[0]: char a
 *     |    |            char padding
 *     |    |            ((char *)&b)[0]
 *     |____|            ((char *)&b)[1]
 *m[1] |    |      t[1]: char a
 *     |    |            char padding
 *     |    |            ((char *)&b)[0]
 *     |____|            ((char *)&b)[1]
 *
 *    high addr
 */

struct test t[2];

int main(void)
{
	printf("sizeof struct test is %u\n", sizeof(struct test));
	printf("sizeof struct t[2] is %u\n", sizeof(t));

	return 0;
}
