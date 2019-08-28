#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#define MAPSIZE 100 /* 共享内存大小， 100 字节 */

int main(int argc, char **argv)
{
    int shmid;
    char *ptr;
    sem_t *semid;

    if (argc != 2) {      /* 参数 argv[1]指定共享内存和信号量的名字 */
        printf("usage: %s <pathname>\n", argv[0]);
        return -1;
    }

    shmid = shm_open(argv[1], O_RDWR|O_CREAT, 0644);     /* 创建共享内存对象 */
    if (shmid == -1) {
        printf( "open shared memory error\n");
        return -1;
    }

    ftruncate(shmid, MAPSIZE);     /* 设置共享内存大小 */

    /* 将共享内存进行映射 */
    ptr = mmap(NULL, MAPSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    strcpy(ptr,"\0");

    semid = sem_open(argv[1], O_CREAT, 0644, 0);     /* 创建信号量对象 */
    if (semid == SEM_FAILED) {
        printf("open semaphore error\n");
        return -1;
    }

    sem_wait(semid);                          /* 信号量等待操作，等待客户端修改共享内存 */
    printf("server recv:%s",ptr);      /* 从共享内存中读取值 */

    strcpy(ptr,"\0");

    munmap(ptr, MAPSIZE);     /* 取消对共享内存的映射 */
    close(shmid);                           /* 关闭共享内存 */
    sem_close(semid);                /* 关闭信号量 */
    sem_unlink(argv[1]);            /* 删除信号量对象 */
    shm_unlink(argv[1]);            /* 删除共享内存对象 */

    return 0;
}