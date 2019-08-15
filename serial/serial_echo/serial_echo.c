/*  串口通讯示例*/


#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <error.h>
#include <string.h>
#include <errno.h>

#define STTY_DEV  "/dev/ttymxc0"
#define BUFF_SIZE 512
extern int errno;

int main()
{
    int stty_fd, n;
    int i=0;
    char buffer[BUFF_SIZE];
    char Send[] = "Hello Embed Fire\n";
    struct termios opt;

    stty_fd = open(STTY_DEV, O_RDWR);

    if (-1 == stty_fd)
    {
        perror("open device");
        return 0;
    }

    printf("Open device success, waiting user input ...\n");

    tcgetattr(stty_fd, &opt);     // 获取串口配置
    tcflush(stty_fd, TCIOFLUSH);    // 同时刷新收到的数据但是不读，并且刷新写入数据但不传送

    /* 设置波特率 115200 */
    cfsetispeed(&opt, B115200);
    cfsetospeed(&opt, B115200);

    /* 设置 8 位数据位 */
    opt.c_cflag &= ~CSIZE;
     opt.c_cflag |= CS8;

     /* 设置为无奇偶校验位 */
     opt.c_cflag &= ~PARENB;
     opt.c_iflag  &= ~INPCK;

     /* 设置 1 位停止位 */
     opt.c_cflag &= ~CSTOPB;

     //opt.c_iflag &= ~(IXOFF | IXON | ICRNL);

     /* 设置超时时间 - 15S */
     opt.c_cc[VTIME] = 150;
     opt.c_cc[VMIN]  = 0;

     /* 将设置写入设备中 */
     if (0 != tcsetattr(stty_fd, TCSANOW, &opt))
     {
	    perror("set baudrate");

	    return -1;
     }

    tcflush(stty_fd, TCIOFLUSH);     // 同时刷新收到的数据但是不读，并且刷新写入数据但不传送

	printf("b = %d\n", cfgetospeed(&opt));

    write(stty_fd, Send, sizeof(Send));

    while (1)
    {
        n = read(stty_fd, buffer, BUFF_SIZE);

        if (n <= 0)
        {
            perror("read data ");
            close(stty_fd);
            return 0;
        }
        buffer[n] = '\0';

        printf("Receive %d : %s\n", n,  buffer);

        if (0 == strncmp(buffer, "quit", 4))
        {
            printf("Program will exit!\n");
            break;
        }
    }
    

    close(stty_fd);

    return 0;
}
