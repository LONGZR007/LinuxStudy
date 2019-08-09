// 创建进程 并等待子进程结束

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	pid_t pid_wait;
	int status;

	pid = fork();    // 创建一个进程

	if (-1 == pid)
	{
		printf("Error to create new process!\n");
		return 0;
	}
	else if (pid ==  0)
	{
		printf("Child process!\n");
	}
	else
	{	
		printf("Parent process! Child process ID: %d!\n", pid);
		
		pid_wait = waitpid(pid, &status, 0);

		printf("Child process %d returned!\n", pid_wait);
		
	}

	return 0;
}
