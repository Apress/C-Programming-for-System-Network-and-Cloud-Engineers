#include<stdio.h>
#include<time.h>
void ArrayInfo()
{
	printf("Accessing elements of the array");
}


int ExprsOpt()
{
	int a=2;
	int b=3;
	int d=4;
	int e=5;
	int f = a*b;
	int g = b+a*b;
	for (int i=0;i<100;i++)
	{	
		d = b*120;
		int g = d/(i+1);
	}
	return g;
}
int loopOpt1()
{
	int d;
	for(int i=0;i<5;i++)
	{
		d = d+i;
	}
	return d;
}
void loopOpt2()
{
        int a[50];
	int b[50];
        for(int i=0;i<50;i++)
        {
                a[i]=i;
        }
        for(int i=0;i<50;i++)
        {
		printf("%d",a[i]);
                b[i]=i*2;
		printf("%d",b[i]);
        }
}
int main()
{

	ExprsOpt();
	loopOpt1();	
	loopOpt2();	
	ArrayInfo();


}

