// exec 族函数调用示例

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *env_init[] = {"USER=peng","HOME=/home/peng/", NULL};    /* 为子进程定义环境变量 */

int main(int argc, char *argv[]){
	pid_t pid;

	if ((pid = fork()) < 0){
		perror("fork error");
	}else if (pid == 0){
		execle("sample",  "sample", "hello", "world", (char *)0, env_init);    // 子进程转载新程序"/home/long/GitHub/LinuxStudy/exec_process_eg/
		perror("execle error");         // execle 失败才会执行
		exit(-1);
	} else{
		exit(0);     // 父进程退出
	}

	return -1;
}
