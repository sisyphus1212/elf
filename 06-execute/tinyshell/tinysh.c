// 来自网络：60行C代码实现一个shell，并做了多处改进
//
// tinysh.c
// gcc tinysh.c -o tinysh
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define CMD_QUIT        "quit\n"
#define CMD_QUIT_LEN    sizeof(CMD_QUIT)
#define CMD_BUF_LEN	512
char cmd[CMD_BUF_LEN] = {0};

void fork_and_exec(char *cmd, int pin, int pout)
{
    if (fork() == 0) {
        if (pin != -1) {
            dup2 (pin, 0);
            close(pin);
        }
        if (pout != -1) {
            dup2 (pout, 1);
            close(pout);
        }
        system(cmd);
        exit(0);
    }
    if (pin != -1)
	close(pin);
    if (pout != -1)
	close(pout);
}

int execute_cmd(char *cmd, int in)
{
	int status;
	char *p = cmd;
	int pipefd[2];

	while (*p) {
		switch (*p) {
		case '|':
			*p++ = 0;
			pipe(pipefd);
			fork_and_exec(cmd, in, pipefd[1]);
			execute_cmd(p, pipefd[0]);
			return 0;
		default:
			p++;
		}
	}
	fork_and_exec(cmd, in, -1);
	while(waitpid(-1, &status, WNOHANG) != -1);
	return 0;
}

int main(int argc, char **argv)
{
	while (1) {
		printf("\ntiny sh>> ");
		fgets(cmd, CMD_BUF_LEN, stdin);
		printf("\n");

		//printf("... cmd: %s\n", cmd);

		if (strncmp(cmd, CMD_QUIT, CMD_QUIT_LEN) == 0) {
			exit(0);
		} else {
			execute_cmd(cmd, -1);
		}
	}
	return 0;
}
