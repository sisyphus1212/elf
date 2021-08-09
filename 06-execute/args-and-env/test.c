#include <unistd.h>  /* environ */
#include <stdlib.h>  /* getenv */
#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
	printf("envp[0]: %s\n", envp[0]);

	printf("getenv(\"PATH\"): %s\n", getenv("PATH"));

	printf("environ[0]: %s\n", environ[0]);  /* equals to envp arguments */

	return 0;
}
