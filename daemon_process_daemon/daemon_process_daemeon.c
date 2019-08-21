// 创建守护进程-使用daemon函数

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int main(void)
{
	int fd;
	time_t curtime;

	if (daemon(0, 0) == -1)    // 创建一个守护进程 第一个0：工作目录设置为/ 第二个0：标准输入输出重定向到/dev/null文件中
	{
		perror("damone error");
		exit(-1);
	}

	fd = open("/tmp/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0664);

	if (fd < 0)
	{
		perror("open /tmp/daemon error");
		exit(0);
	}

	while(1){
		curtime = time(0);
		char *timestr = asctime(localtime(&curtime));
		write(fd, timestr, strlen(timestr));
		sleep(60);
	}
	
	close(fd);

	return 0;
}
