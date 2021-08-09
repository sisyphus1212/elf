/* Author: Wu Zhangjin, Wechat: tinylab */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    size_t length;
    ssize_t s;

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "%s file offset [addr]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    offset = atoi(argv[2]);
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 4) {
        sscanf(argv[3], "%p", &addr);
    }
    length = sb.st_size - offset;

    addr = mmap((void *)addr, length + offset - pa_offset, PROT_READ|PROT_WRITE|PROT_EXEC,
                MAP_PRIVATE|MAP_FIXED, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

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
