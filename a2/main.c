#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//wrote them as individual programs, ran into issues merging them
int main()
{
	printf("Sorting\n");
	pid_t id = fork();
	if (id == 0)
	{
		char *argv[]={"./P11",NULL};
		execvp(argv[0], argv);
	}
	else
	{
		wait(&id);
	}

	id = fork();
	if (id == 0)
	{
		char *argv[]={"./P12",NULL};
		execvp(argv[0], argv);
	}
	else
	{
		wait(&id);
	}

	printf("\nConvex Hull\n");
	id = fork();
	if (id == 0)
	{
		char *argv[]={"./P21",NULL};
		execvp(argv[0], argv);
	}
	else
	{
		wait(&id);
	}
	printf("\n");
	id = fork();
	if (id == 0)
	{
		char *argv[]={"./P22",NULL};
		execvp(argv[0], argv);
	}
	else
	{
		wait(&id);
	}
}