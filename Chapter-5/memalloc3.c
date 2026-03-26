#include<stdio.h>
#include<stdlib.h>
int** arrayofVarSizeBlocks(int n)
{
        int **p=(int**)calloc(n,sizeof(int*));
	if (p!=NULL)
	{
        	for (int i=0;i<n;i++)
        	{
			p[i] = (int*)calloc(1,sizeof(int)*(i+1));
			if (p[i]!=NULL)
			{
				for (int j=0;j<i+1;j++)
				{
					p[i][j]=j;
				}
			}
			else
				return NULL;
        	}
		return p;
	}
	else
	{
		return NULL;
	}
}

int** extendVarSizeBlocks(int **p,int m,int n,int k)
{
        int **tvb;
	if (p==NULL)
	{
		return NULL;
	}
	else
	{
		tvb=(int**)realloc(p,n*sizeof(int*));
		if (tvb==NULL)
		{
			return NULL;
		}
		else
		{
			printf("Old memory block contents\n");
			for (int i=0;i<m;i++)
			{
				for (int j=0;j<i+1;j++)
				{
					printf("%d ",tvb[i][j]);
				}
				printf("\n");
			}
			printf("New memory block contents\n");
			for (int i=m;i<n;i++)
                	{
                        	tvb[i] = (int*)calloc(1,sizeof(int)*(k));
                        	if (tvb[i]!=NULL)
                        	for (int j=0;j<k;j++)
                        	{
                                	tvb[i][j]=j;
					printf("%d ",tvb[i][j]);
                        	}
				else
				{
					return NULL;
				}
				printf("\n");
                	}
			return tvb;
		}
	}
}
int main()
{
	int **ap = arrayofVarSizeBlocks(10);
	if (ap==NULL)
	{
		printf("Allocation is failed\n");
		return 0;
	}
	else
	{
		int **dp = extendVarSizeBlocks(ap,10,15,10);

		if (dp==NULL)
		{
			printf("Allocation is failed\n");
			return 0;
		}
		if (dp!=NULL)
		{
			for (int i=0;i<15;i++)
			{
				free(dp[i]);
				dp[i]=NULL;
			}
			free(dp);
			dp=NULL;
		}
	}
}
