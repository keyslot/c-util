#include <stdio.h>
/* Pow recursive */
int rpow(int,int);

int main(void)
{
	printf("3 ^ 3 = %d\n",rpow(3,3));
	return 0;
}

int
rpow(int i, int n) 
{ 
	return (n == 0 ? 1 : i * rpow(i,n-1));
}



