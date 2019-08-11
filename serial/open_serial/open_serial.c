// 打开一个串口    /* 在 /dev 下可以看到有那些串口 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
int main()
{
	int fd;

	fd = open("/dev/ttyUSB0", O_RDWR);    // 通过读写的方式打开串口

	if (fd == -1)
	{
		perror("open ttyUSB0");
		return 0;
	}
	printf("Open ttyUSB0 OK\n");

	close(fd);

	return 0;
}
