#include <stdio.h>
#include <unistd.h>

#if 1
asm(".pushsection .interp,\"a\"\n"
    "        .ascii \"/lib32/ld-linux.so.2\\x00\"\n"
    ".popsection");

    /* .ascii above equals to .string \"/lib32/ld-linux.so.2\"\n */
#else
asm(".pushsection .interp,\"a\"\n"
    "        .incbin \"interp.section.txt\"\n"
    ".popsection");
#endif

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
