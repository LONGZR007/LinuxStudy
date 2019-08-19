#include <stdio.h>
#include "sum.h"
   
int main (void)
{
    int x = 0;
    int y = 0;
   // printf("1+1=%d\n", sum(1,1));Please enter the value of x
   printf("Please enter the value of x and y :\n");
   scanf("%d %d", &x, &y);

    printf("x+y=%d\n", sum(x, y));
	return 0;
}
