/* 共享内存写示例 */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int shmid;
	char *ptr;
	char *shm_str = "string in a sharr memroy";

	shmid = shmget(0x90, 1024, SHM_W|SHM_R|IPC_CREAT|IPC_EXCL); // 创建共享内存

	if (-1 == shmid)
	{
		perror("create shrae memory");
	}

	ptr = (char *)shmat(shmid, 0, 0);    // 获取共享内存的地址

	if ((void *)-1 == ptr)
	{
		perror("get shaer mmeory");
	}

	strcpy(ptr, shm_str);
	shmdt(ptr);    // 分离共享内存

	return 0;
}
