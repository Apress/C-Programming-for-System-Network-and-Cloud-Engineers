#include<stdio.h>
long unsigned int fact(long unsigned int n)
{
//	int a[256];
	if (n==0 || n==1)
		return 1;
	else 
		return n*fact(n-1);
}

int main()
{
	fact(7);
}
