// 进程通讯示例—管道

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2];
	pid_t pid;
	char buf[64] = "I'm parent process!\n";    // 父进程要写入管道的信息
	char line[64];

	if (0 != pipe(fd))     // 创建一个管道
	{
		fprintf(stderr,"Fail to create pipe\n");
		return 0;
	}

	pid = fork();    // 创建进程

	if (pid < 0)
	{
		fprintf(stderr, "Fail to create process\n");
		return 0;
	}
	else if (pid > 0)
	{
		close(fd[0]);    // 关闭读管道，使得父进程只能写入管道
		write(fd[1], buf, strlen(buf));    // 将消息写进管道
		close(fd[1]);      // 关闭写管道
	}
	else 
	{
		close(fd[1]);    // 关闭写管道，使得子进程只能从管道读数据
		read(fd[0], line, 64);    // 从管道读数据
		close(fd[0]);    // 关闭读管道
		printf("DATA Form Parent: %s\n", line);
	}

	return 0;
}
