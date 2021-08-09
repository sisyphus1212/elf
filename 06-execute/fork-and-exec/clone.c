/* ref: https://blog.csdn.net/gogokongyin/article/details/51178257 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define CHILD_STACK 8192

int val = 1;
void *stack;

int do_whatever() {
    val = 20;

    printf("[CHILD] pid: %d, val: %d\n", getpid(), val);

    free(stack);

    _exit(0);
}

int main(void)
{
    val = 5;
    stack = malloc(CHILD_STACK);       /* 为子进程申请系统堆栈 */
    if (!stack) {
        printf("allocating stack failed\n");
        _exit(1);
    }

    printf("[PARENT] creating son thread!\n");
    clone(&do_whatever, (char *)stack + CHILD_STACK,
	/*CLONE_VM|*/ CLONE_VFORK, 0); /* 创建子线程 */
    printf("[PARENT] pid: %d, val: %d\n", getpid(), val);
}
