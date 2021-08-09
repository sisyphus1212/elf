/* test1.c */

#include <dlfcn.h>      /* dlopen, dlsym, dlerror */
#include <stdlib.h>     /* exit */
#include <stdio.h>      /* printf */

#define LIB_SO_NAME     "./libmyprintf.so"
#define FUNC_NAME "myprintf"

typedef int (*func)(char *);

int main(void)
{
        void *h;
        char *e;
        func f;

        h = dlopen(LIB_SO_NAME, RTLD_LAZY);
        if ( !h ) {
                printf("failed load libary: %s\n", LIB_SO_NAME);
                exit(-1);
        }
        f = dlsym(h, FUNC_NAME);
        e = dlerror();
        if (e != NULL) {
                printf("search %s error: %s\n", FUNC_NAME, LIB_SO_NAME);
                exit(-1);
        }
        f("Hello World");

        exit(0);
}
