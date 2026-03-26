#include<stdio.h>
int hrecfunc(int n)
{
	int a[1024];
	if (n==0)
	{
		return 1;
	}
	else
	{
		for (int i=0;i<10;i++)
		{
			a[i]=i*i;
		}
		hrecfunc(n-1);
	}

}
int lrecfunc(int n)
{
        int a[100];
        if (n==0)
        {
                return 1;
        }
        else
        {
                for (int i=0;i<10;i++)
                {
                        a[i]=i*i;
                }
                lrecfunc(n-1);
        }

}

int main()
{
	int n=20020;
//	if (n<20000)
	{
		lrecfunc(n);
	}
	n=2020;
//	if (n<=2000)
	{

		hrecfunc(2000);
	}
}
