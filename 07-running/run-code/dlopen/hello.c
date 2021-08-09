/* Author: Wu Zhangjin, Wechat: tinylab */

#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <dlfcn.h>

void hello(void)
{
	printf("hello dlopen\n");
}

int main(void)
{
	void *handle;
        void (*func)(void);
        char *error;

        handle = dlopen(NULL, RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "%s\n", dlerror());
            return EXIT_FAILURE;
        }

        dlerror();    /* Clear any existing error */

        func = (void (*)(void)) dlsym(handle, "hello");

        error = dlerror();
        if (error != NULL) {
            fprintf(stderr, "%s\n", error);
            return EXIT_FAILURE;
        }

	func();
        dlclose(handle);

	return 0;
}
