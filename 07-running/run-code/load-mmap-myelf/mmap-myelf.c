/* Author: Wu Zhangjin, Wechat: tinylab */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <endian.h>
#include <unistd.h>     /* fork, execlp */
#include <sys/wait.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* magic: 0x7F M Y E */
/* x86 little endian */
#define mye_magic 0x45594d7f

struct mye_header {
	int magic;
	int ioffset;
	int doffset;
};

int
main(int argc, char *argv[])
{
    char *addr = NULL;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    int inst_offset, data_offset;
    size_t length, context_length;
    ssize_t s;
    int ret = EXIT_SUCCESS;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "%s file [addr]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    offset = 0;                         /* not used by me */
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        sscanf(argv[2], "%p", &addr);
    }
    length = sb.st_size - offset;

    addr = mmap((void *)addr, length + offset - pa_offset, PROT_READ|PROT_WRITE|PROT_EXEC,
                MAP_PRIVATE|MAP_FIXED|MAP_POPULATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    /* check file magic */
    struct mye_header *mh = (struct mye_header *)addr;

    if (mh->magic != mye_magic) {
        printf("ERR: magic %x not support\n", mh->magic);
        ret = EXIT_FAILURE;
        goto unmap;
    } else {
        printf("LOG: magic 0x7FMYE detected\n");
    }

    /* get inst and data offset */
    inst_offset = be32toh(mh->ioffset);
    data_offset = be32toh(mh->doffset);

    context_length = length - sizeof(struct mye_header);
    if (inst_offset < context_length - 4) {
        printf("LOG: ioffset %x valid\n", inst_offset);
    } else {
        printf("ERR: ioffset %x invalid\n", inst_offset);
        ret = EXIT_FAILURE;
        goto unmap;
    }

    if (data_offset < context_length - 4) {
        printf("LOG: doffset %x valid\n", data_offset);
    } else {
        printf("ERR: doffset %x invalid\n", data_offset);
        ret = EXIT_FAILURE;
        goto unmap;
    }

    /* get entry point */
    addr = (char *)addr + sizeof(struct mye_header);

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

unmap:
    munmap(addr, length + offset - pa_offset);

    //printf("exit\n");

    exit(ret);
}
