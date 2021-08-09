/* Author: Wu Zhangjin, Wechat: tinylab */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     /* fork, execlp */
#include <sys/wait.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int
main(int argc, char *argv[])
{
    char *addr = NULL;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    int inst_offset, data_offset;
    size_t length;
    ssize_t s;

    if (argc < 4 || argc > 5) {
        fprintf(stderr, "%s file inst_offset data_offset [addr]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    inst_offset = atoi(argv[2]);
    data_offset = atoi(argv[3]);

    offset = 0;                         /* not used by me */
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 5) {
        sscanf(argv[4], "%p", &addr);
    }
    length = sb.st_size - offset;

    addr = mmap((void *)addr, length + offset - pa_offset, PROT_READ|PROT_WRITE|PROT_EXEC,
                MAP_PRIVATE|MAP_FIXED|MAP_POPULATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    /* dynamic linking: update the data address */
    /* inst offset are gotten from this command: $ objdump -dr hello.o or readelf -r hello.o */
    /* data offset are gotten from this command: $ readelf -S hello.o  | egrep " .text|Size" */
    *(unsigned int *)(addr + inst_offset) = (uint)addr + data_offset;

    /* flush icache: https://gcc.gnu.org/onlinedocs/gcc-8.3.0/gcc/Other-Builtins.html */
    __builtin___clear_cache(addr, addr + length + offset - pa_offset);

    int pid, status = 0;
    if ((pid = fork()) == 0) {
        /* execute it */
        ((void (*)(void))addr)();
    }

    wait(&status);

    munmap(addr, length + offset - pa_offset);

    //printf("exit\n");

    exit(EXIT_SUCCESS);
}
