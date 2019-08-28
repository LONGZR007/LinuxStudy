/* 线程创建示例 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid){ /* 线程函数 */
    long tid;
    tid = (long)threadid;

    printf("Hello World! It's me, thread #%ld!\n", tid); /* 打印线程对应的参数 */

    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for(t=0; t<NUM_THREADS; t++){ /* 循环创建 5 个线程 */
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t); /* 创建线程 */
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    printf("In main: exit!\n");
    pthread_exit(NULL); /* 主线程退出 */

    return 0;
}
