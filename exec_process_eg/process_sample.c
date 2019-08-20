// exec 族函数使用示例

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;     // 全局环境变量

int main(int argc, char *argv[]){
	int i;

	printf("argc = %d\n", argc);    // 打印参数个数
	printf("args:");
	for(i=0; i<argc; i++)
		printf("%s", argv[i]);    // 打印参数表
	printf("\n");

	i = 0;
	while(environ[i])
		puts(environ[i++]);     // 打印环境变量表

	printf("\n");

	return 0;
}
