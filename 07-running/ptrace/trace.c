/* From: https://stackoverflow.com/questions/13426561/how-to-use-ptrace2-to-change-behaviour-of-syscalls */

#include <stdio.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>     /* fork, execlp */

int main(int argc, char **argv)
{
    int status = 0, pid, r;
    struct user_regs_struct uregs;

    if ((pid = fork()) == 0) {
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGINT);
        r = getpid();
        printf("%d\n", r);
    } else {
        wait(&status);
        ptrace(PTRACE_SYSCALL, pid, 0, 0);
        wait(&status);
        ptrace(PTRACE_GETREGS, pid, 0, &uregs);

        /* this prints the syscall number of getpid */
        printf("syscall nr: %ld\n", uregs.orig_eax);
        /* 64 is syscall number of getppid */
        uregs.orig_eax = 64;
        ptrace(PTRACE_SETREGS, pid, 0, &uregs);
        ptrace(PTRACE_CONT, pid, 0, 0);
        wait(&status);
        if(WIFEXITED(status))
            printf("we're done\n");
    }
}
