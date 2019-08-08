#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main ()
{
	int fd,file_mode;
	char buf[64] = "this is a posix file! (line1)\n";
	off_t curr_pos;

	fd = open("./posix.data", O_CREAT|O_RDWR|O_EXCL, S_IRWXU);

	if (-1 == fd)
	{
		switch (errno)
		{
			case EEXIST:
				printf("File exist!\n");
				break;

			default:
				printf("open file fail!\n");
		}

		return 0;
	}

	write(fd, buf, strlen(buf));

	curr_pos = lseek(fd, 0, SEEK_CUR);

	printf("File Point at: %d\n", (int) curr_pos);

	lseek(fd, 0, SEEK_SET);

	strcpy(buf, "File Pointer Mvoed!\n");
	write(fd, buf, strlen(buf));

	file_mode = fcntl(fd, F_GETFL);

	if (-1 != file_mode)
	{
		switch(file_mode & O_ACCMODE)
		{
			case O_RDONLY:
				printf("file mode is READ ONLY\n");
				break;
			case O_WRONLY:
				printf("file mode is WRITE ONLY\n");
				break;
			case O_RDWR:
				printf("file mode is READ & WRITE\n");
				break;
		}
	}

	close(fd);

	return 0;
}
