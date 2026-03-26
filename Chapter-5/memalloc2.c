#include<stdio.h>
#include<stdlib.h>
int* arrayofBlocks(int n, int s)
{
	int *p=(int*)calloc(n,sizeof(int)*s);
	for (int i=0;i<n;i++)
	{
		int k=0;
		for (int j=0;j<s;j++)
		{
			p[k]=k++;
		}
	}

	for (int i=0;i<n;i++)
        {
                int k=0;
                for (int j=0;j<s;j++)
                {
                        printf("%d ",p[k]);
			k++;
                }
		printf("\n");
        }
	return p;

}
int** arrayofVarSizeBlocks(int n)
{
        int **p=(int**)calloc(n,sizeof(int*));
	if (p!=NULL)
	{
         		
        	for (int i=0;i<n;i++)
        	{
			p[i] = (int*)calloc(1,sizeof(int)*(i+1));
			if (p[i]!=NULL)
			for (int j=0;j<i+1;j++)
			{

				p[i][j]=j;
			}
        	}

        	for (int i=0;i<n;i++)
        	{
                	for (int j=0;j<i+1;j++)
                	{
                        	printf("%d ",p[i][j]);
                        
                	}
			printf("\n");
        	}
		return p;
	}
	return NULL;

}
int main()
{
	printf("Equal size memory blocks\n");
	int *blocks=arrayofBlocks(10,20);
	if (blocks!=NULL)
	{
		free(blocks);
		blocks=NULL;
	}
	printf("Variable size memory blocks\n");
	int **ap = arrayofVarSizeBlocks(10);
	if (ap!=NULL)
	{
		for (int i=0;i<10;i++)
		{
			free(ap[i]);
			ap[i]=NULL;
		}
		free(ap);
		ap=NULL;
	}
	else
	{
		return 0;
	}
}

