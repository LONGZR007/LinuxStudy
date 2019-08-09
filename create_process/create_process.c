// 创建进程

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	pid = fork();    // 创建一个进程

	if (-1 == pid)
	{
		printf("Error to create new process!\n");
	}
	else if (pid ==  0)
	{
		printf("Child process!\n");
	}
	else
	{
		
		printf("Parent process! Child process ID: %d!\n", pid);
	}

	return 0;
}
