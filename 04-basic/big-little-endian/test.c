#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Convert */

int main(void)
{
	uint32_t data = 0x01020304;

	printf("                   sizeof data is %u\n\n", sizeof(data));
	printf("                   addr       data\n\n");
	printf("                   %p 0x%0x\n\n", &data, data);
	printf("                   %p 0x%0x\n", &(((char *)&data)[0]),((char *)&data)[0]);
	printf("                   %p 0x%0x\n", &(((char *)&data)[1]),((char *)&data)[1]);
	printf("                   %p 0x%0x\n", &(((char *)&data)[2]),((char *)&data)[2]);
	printf("                   %p 0x%0x\n\n", &(((char *)&data)[3]),((char *)&data)[3]);

	/* Little endian: LSB is the 1st byte */
        if ((data & 0xff) == ((char *)&data)[0]) {
		printf("                        Host: Little endian\n\n");
		printf("                          To: Big endian\n\n");
		data = htobe32((uint32_t)data);
	} else {
		printf("                        Host: Big endian\n\n");
		printf("                          To: Little endian\n\n");
		data = htole32((uint32_t)data);
	}

	printf("                   addr       data\n\n");
	printf("                   %p 0x%0x\n\n", &data, data);
	printf("                   %p 0x%0x\n", &(((char *)&data)[0]),((char *)&data)[0]);
	printf("                   %p 0x%0x\n", &(((char *)&data)[1]),((char *)&data)[1]);
	printf("                   %p 0x%0x\n", &(((char *)&data)[2]),((char *)&data)[2]);
	printf("                   %p 0x%0x\n\n", &(((char *)&data)[3]),((char *)&data)[3]);

	return 0;
}
