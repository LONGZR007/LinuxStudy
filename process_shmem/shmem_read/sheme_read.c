// 内存共享——读

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int shmid;                 // 内存共享 ID
	char *ptr;

	shmid = shmget(0x90, 1024, SHM_W|SHM_R|IPC_EXCL);    // 根据 KEY = 0x90 获取共享内存的 ID

	if (-1 == shmid)
	{
		perror("create share memory");
	}

	ptr = shmat(shmid, 0, 0);    // 通过共享内存的ID获取共享内存的首地址

	if ((void *)1 == ptr)
	{
		perror("get share memory");
	}

	printf("string in share memory : %s\n", ptr);

	shmdt(ptr);    // 分离共享内存

	return 0;
}
