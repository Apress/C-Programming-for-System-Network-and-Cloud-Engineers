#include<stdio.h>
#include<stdlib.h>
int* GetBuffer(int n)
{
	int *p = (int*)malloc(sizeof(int)*n);
	//printf("%d",sizeof(p));
	return p;
}
int* BufferCopy(int *src, int m, int *dst, int n)
{
	
	for (int i=0;i<m;i++)
	{
		dst[i]=src[i];	
	}
	return dst;

}
int* extendBuff(int *src,int m,int n,int ch)
{
	int *tbuf;
	tbuf=realloc(src,n*sizeof(int));
	if (tbuf==NULL)
	{
		printf("exteding failed\n");
		return src;
	}
	else
	{
		for (int i=m;i<n;i++)
        	{
                	tbuf[i]=ch;
        	}
        	return tbuf;
	}

}

int main()
{
	int *m1 = GetBuffer(10);
	if (m1!=NULL)
	{	
		printf("Dynamically allocated memory block contents\n");
		for (int i=0;i<10;i++)
		{	
			m1[i]=i;
			printf("%d ", m1[i]);
		}
		printf("\n");
	}
	else
	{
		return 0;
	}	

	int *m2 = GetBuffer(20);
	if (m2!=NULL)
	{
		m2 = BufferCopy(m1,10,m2,20);
		free(m1);
		m1=NULL;
		printf("Copied memory block contents\n");
		for (int i=10;i<20;i++)
        	{
			m2[i]=i;
                	printf("%d ", m2[i]);
        	}
        	printf("\n");

		for (int i=0;i<20;i++)
        	{
                	printf("%d ", m2[i]);
        	}
        	printf("\n");
		free(m2);
		m2=NULL;
	}

	int *p = GetBuffer(10);
	if (p!=NULL)
	{
		printf("Dynamically allocated memory block contents\n");
		for (int i=0;i<10;i++)
		{
			p[i]=i;
			printf("%d ", p[i]);
		}
		printf("\n");
		
		p=extendBuff(p,10,20,1);
		printf("Extended memory block contents\n");
		for (int i=0;i<20;i++)
		{
			printf("%d ", p[i]);
		}

		printf("\n");
		free(p);
		p=NULL;
	}

}

