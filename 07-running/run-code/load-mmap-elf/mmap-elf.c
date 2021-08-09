/* Author: Wu Zhangjin, Wechat: tinylab */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <elf.h>
#include <unistd.h>     /* fork, execlp */
#include <sys/wait.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* magic: 0x7F E L F */
/* x86 little endian */
#define elf_magic 0x464c457f

int
main(int argc, char *argv[])
{
    char *addr = NULL, *entry = NULL;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t headers_length, length;
    ssize_t s;
    int ret = EXIT_SUCCESS;

    if (argc < 1 || argc > 2) {
        fprintf(stderr, "%s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    /* read ELF header and 5 program header, 2 may be enough for our minimal elf binary */
    headers_length = sizeof(Elf32_Ehdr) + 5 * sizeof(Elf32_Phdr);
    if (headers_length >= sb.st_size)
        headers_length = sb.st_size;

    addr = mmap((void *)addr, headers_length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    /* check file magic */
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)addr;
    int magic = *((int *)&ehdr->e_ident);

    if (magic != elf_magic) {
        printf("ERR: magic %x not support\n", magic);
        ret = EXIT_FAILURE;
        goto unmap_addr;
    } else {
        ; // printf("LOG: ELF detected\n");
    }

    /* scan loadable and executable program header */
    int i;
    Elf32_Phdr *p, *phdr_start = (Elf32_Phdr *)((char *)addr + ehdr->e_phoff);
    for (i = 0; i < ehdr->e_phnum; i++) {
       p = phdr_start + i;
       if ((p->p_type == PT_LOAD) && (p->p_flags & PF_X == PF_X)) {
           // printf("LOG: Loadable and executable program header found: %d\n", i);
           break;
       }
    }

    char *vaddr = NULL;
    char flags = 0;
    for (p; p < phdr_start + ehdr->e_phnum; p++) {
        pa_offset = p->p_offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */
        //printf("%d\n", p->p_filesz);

        /* load the program context to memory */
        if ((p->p_flags & PF_X) == PF_X)
            flags = PROT_READ | PROT_EXEC;
	else
            flags = PROT_READ;
        mmap((void *)p->p_vaddr, p->p_filesz + p->p_offset - pa_offset, flags, MAP_PRIVATE|MAP_FIXED|MAP_POPULATE, fd, pa_offset);
    }

    /* get entry point */
    entry = (char *)ehdr->e_entry;

    int pid, status = 0;
    if ((pid = fork()) == 0) {
        /* execute it */
        ((void (*)(void))entry)();
    }

    wait(&status);

    for (p--; p > phdr_start; p--) {
        //printf("%d\n", p->p_filesz);

        pa_offset = p->p_offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */
        munmap((void *)p->p_vaddr, p->p_filesz + p->p_offset - pa_offset);
    }
unmap_addr:
    munmap(addr, headers_length);

    exit(ret);
}
