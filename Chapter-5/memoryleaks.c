#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void ivr()
{
	int *p=(int*)malloc(sizeof(int)*10);
	int i;
	for (i=0;i<10;i++)
	{
		p[i]=0;
	}

	for (i=0;i<12;i++)
	{
		printf("%d",p[i]);
	}
	free(p);

}
void ivw()
{
	int *p=(int*)malloc(sizeof(int)*10);
	int i;
	for (i=0;i<10;i++)
	{
		p[i]=0;
	}
	for (i=0;i<12;i++)
	{
		p[i]=0;
	}

	free(p);
}
void uninitialize()
{
	int *p=(int*)malloc(sizeof(int)*10);
	if (p!=NULL)
	{
//	memset(p,0,10);
	for(int i=0;i<10;i++)
	{
		printf("%d",p[i]);
	}
	}
}

int *accesserr()
{
	int a=100;
	return &a;
}

int* leak()
{
	int *p=(int*)malloc(sizeof(int)*10);
	return p;
}

int main()
{
	char *p;
//	ivr();
//	ivw();
	uninitialize();


/*	int *p1=accesserr();
	*p1=300;
*/

//	int *q=leak();
//	free(q);
//	q[0]=100;
}
