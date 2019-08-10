// 进程推出示例

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bye(void)
{
	printf("That was all, folks\n");
}

void bye1(void)
{
	printf("This should called first\n");
}

int main()	
{
	if(atexit(bye) != 0)     // 退出并检查错误
	{
		fprintf(stderr, "cannton set exit function bye\n");
		return EXIT_FAILURE;
	}

	if(atexit(bye1) != 0)     // 退出并检查错误
	{
		fprintf(stderr, "cannton set exit function bye1\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
