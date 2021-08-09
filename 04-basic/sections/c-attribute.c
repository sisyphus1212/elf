#include <stdio.h>
#include <unistd.h>

const char interp[] __attribute__((section(".interp"))) = "/lib32/ld-linux.so.2";

int main(void)
{
        printf("hello\n");

        return 0;
}

void _start(void)
{
        int ret;

        ret = main();
        _exit(ret);
}
