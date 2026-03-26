#include<stdio.h>
int Compute(int n)
{
	int secretCompute(int n)
	{
		int s=0;
		for (int i=0;i<n;i++)
		{
			s=s+i;	
		}
		return s;
	}
	printf("%d",s);
	n=secretCompute(n);
	return n;

}
int main()
{	
	int res=Compute(10);
	printf("Compute: %d",res);
	res=secretCompute(10);
	printf("Compute: %d",res);
}
