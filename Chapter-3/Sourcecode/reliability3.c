#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int g=100;
void ArrayAccess()
{
	static int variable=0;
	float p=0.1;
	int a[8][8];
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			a[i][j]=i*j;
			p = p*i*j;
		}
	}
	for (int i=0;i<8;i++)
        {
                for (int j=0;j<8;j++)
                {
                        printf("%d",a[i][j]);
                }
        }
	for (int i=0;i<8;i++)
        {
                for (int j=0;j<8;j++)
                {
                        printf("%d",a[i][j]);
                }
        }


}
void StringChecks(char *buff)
{
	char ibuff[10];
	strcpy(ibuff,buff);
	printf("Accessing elements of the array %s",ibuff);
}

void DataRangesOperations(int N)
{
	int d;
	d = 100;
	int res;
	for (int i=0;i<N;i++)
	{
		d = d*1000+d*100+d*10;
	}
	if (d!=0)
	{
		N = N%d;
		res = d/N;
	}
}
void ArrayBoundsCheck(int N)
{
	
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	for (int i=0;i<N;i++)
	{
		printf("%d ",a[i]);
	}
}

int main()
{
	
	char *p1 = "abcdefghijk";
	ArrayAccess();
	StringChecks(p1);
//	DataRangesOperations(1024);
	ArrayBoundsCheck(12);
	char *p2 = (char*)malloc(sizeof(char)*11);
	for (int i=0;i<10;i++)
	{
		p2[i]=i+37;
	}
	p2[10]='\0';
//	if (p2!=NULL)
//	{
		StringChecks(p2);
		free(p2);
//	}
	p2[0]='a';
	free(p2);
}

