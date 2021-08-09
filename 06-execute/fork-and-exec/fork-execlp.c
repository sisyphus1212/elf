#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>   /* wait */
#include <unistd.h>     /* fork, execlp */

int main()
{
    int child;
    int status;

    if ( (child = fork()) == 0 ) {  /* child */
        printf("[CHILD]: pid is %d\n", getpid());
        printf("[CHILD]: parent's pid is %d\n", getppid());

        execlp("/usr/bin/test", "/usr/bin/test", (char *)NULL);
        _exit(1);
    } else if (child < 0) {         /* error */
        printf("[PARENT] creating child process failed!\n");
        _exit(0);
    }                               /* parent */

    printf("[PARENT]: pid is %d\n", getpid());

    if ( wait(&status) == child ) {
        printf("[PARENT]: wait for my child exit successfully!\n");
    }
}
