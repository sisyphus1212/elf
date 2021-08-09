#include <stdio.h>
#include <unistd.h>

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
