// 获取环境变量

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *env_path = "PATH";    // 环境变量的名字
	char *env_value = NULL;    // 要获取的环境变量的值

	env_value = getenv(env_path);    // 获取环境变量的值

	if (env_value == NULL)
	{
		printf("Not found!");
	}

	printf("Get Env PATH: %s \n", env_value);

	return 0;
}
