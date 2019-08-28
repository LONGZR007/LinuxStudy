// 进程通讯示例—管道

/*
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
*/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
	exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1) { /* 创建匿名管道 */
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork(); /* 创建子进程 */

	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) { /* 子进程读管道读端 */
		close(pipefd[1]); /* 关闭不需要的写端 */
		while (read(pipefd[0], &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	} else { /* 父进程写 argv[1]到管道 */
		close(pipefd[0]); /* 关闭不需要的读端 */
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]); /* 关闭文件发送 EOF，子进程停止读*/
		wait(NULL); /* 等待子进程退出 */
		exit(EXIT_SUCCESS);
	}
}
