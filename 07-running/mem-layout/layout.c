/*
 * layout.c
 *
 * Author: Wu Zhangjin, Wechat: tinylab
 */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>

#define ARRAY_SIZE 4000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE (SHM_R | SHM_W)        /* user read/write */
#define MMAP_SIZE 10000

                                        /* declare the address relative variables */
extern char __executable_start, __gotplt_start, __data_start, __bss_start, etext, edata, end;
extern char **environ;
char *mmap_addr;
char array[ARRAY_SIZE];         /* uninitialized data = bss */

int main(int argc, char *argv[])
{
    char cmd[32];
    int shmid;
    char *ptr, *shmptr, *func;

    //brk((void *)0xf7500000);    /* change the end of heap space, sbrk() increment it */

    printf("===== memory map =====\n");
    printf(".text:\t%p->%p (__executable_start, code text)\n", &__executable_start, &etext);
    printf(".data:\t%p->%p (__data_start, initilized data)\n", &__data_start, &edata);
    printf(".bss: \t%p->%p (__bss_start, uninitilized data)\n", &__bss_start, &end);

    /* shmid is a local variable, which is stored in the stack, hence, you
     * can get the address of the stack via it*/

    if ( (ptr = malloc(MALLOC_SIZE)) == NULL) {
        printf("malloc error!\n");
        exit(-1);
    }

    printf("heap: \t%p->%p (address of the malloced space)\n", ptr, ptr+MALLOC_SIZE);

    if ( (shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) {
        printf("shmget error!\n");
        exit(-1);
    }

    if ( (shmptr = shmat(shmid, 0, 0)) == (void *) -1) {
        printf("shmat error!\n");
        exit(-1);
    }
    printf("shm  :\t%p->%p (address of shared memory)\n", shmptr, shmptr+SHM_SIZE);

    if (shmctl(shmid, IPC_RMID, 0) < 0) {
        printf("shmctl error!\n");
        exit(-1);
    }

    mmap_addr = mmap(NULL, MMAP_SIZE, PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);

    printf("libs: \t <--%p--> (address of function in libs)\n", (void *)(*(unsigned int *)(&__gotplt_start + 0x0c)));
    printf("mmap: \t <--%p--> (address of mmaped anon space)\n", mmap_addr);
    printf("stack:\t <--%p--> (address of local variables)\n", &shmid);   
    printf("arg:  \t%p (address of arguments)\n", argv);
    printf("env:  \t%p (address of environment variables)\n", environ);

    sprintf(cmd, "cat /proc/%d/maps", getpid());
    system(cmd);

    free(ptr);
    munmap(mmap_addr, MMAP_SIZE);
}
