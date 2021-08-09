/* Author: Wu Zhangjin, Wechat: tinylab */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

typedef unsigned int uint32_t;

#define ROUNDDOWN(a, n)                \
    ({                                 \
        uint32_t __a = (uint32_t) (a); \
        (typeof(a)) (__a - __a%(n));   \
    })

#define ROUNDUP(a, n)                           \
    ({                                          \
        uint32_t __n = (uint32_t) (n);          \
        (typeof(a)) (ROUNDDOWN((a) + __n - 1, __n ));   \
    })

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void
handler(int sig, siginfo_t *si, void *unused)
{
    printf("Got SIGSEGV at address: 0x%lx\n",
           (long) si->si_addr);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int len = 0;
    char *addr = NULL;
    long start = 0, end = 0;
    const long page_size = sysconf(_SC_PAGE_SIZE);
    int inst_offset, data_offset;
    struct sigaction sa;

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "%s file inst_offset data_offset\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        handle_error("sigaction");

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        printf("readdata %s failed\n", argv[1]);
        return -1;
    }

    inst_offset = atoi(argv[2]);
    data_offset = atoi(argv[3]);

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);

    rewind(fp);
    addr = memalign(page_size, len);
    if (addr == NULL) {
        printf("alloc memory failed\n");
        return -1;
    }
    memset(addr, 0, len);

    if (fread(addr, 1, len, fp) != len) {
        printf("read data failed\n");
        return -1;
    }

    start = (long)addr;
    end = (long)ROUNDUP(addr + len, page_size);

    if (mprotect((void*)start, end - start, PROT_READ|PROT_WRITE|PROT_EXEC) == -1) {
        handle_error("mprotect");
    }

    /* dynamic linking: update the data address */
    /* inst offset are gotten from this command: $ objdump -dr hello.o or readelf -r hello.o */
    /* data offset are gotten from this command: $ readelf -S hello.o  | egrep " .text|Size" */
    *(unsigned int *)(addr + inst_offset) = (uint)addr + data_offset;

    int pid, status = -1;
    if ((pid = fork()) == 0) {
        /* execute it */
        ((void (*)(void))addr)();
    }

    wait(&status);

    fclose(fp);
    printf("exec success, ret = %d\n", status);

    return status;
}
