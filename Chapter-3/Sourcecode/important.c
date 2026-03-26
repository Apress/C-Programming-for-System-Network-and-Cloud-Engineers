#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
int search(int *p, int N, int ele)
{
	if (p==NULL)
		return -1;
	else
	{
		int i;
		int index=-1;
		for (i=0;i<N;i++)
		{
			if (p[i]==ele)
			{
				index = i;
				return index;
			}
		}
		return index;
	}

}
int min(int *p, int N)
{
        if (p==NULL)
                return -1;
        else
        {
                int i;
                int min = p[0];
                int index=-1;
                for (i=0;i<N;i++)
                {
                        if (p[i]<=min)
                        {
                                min = p[i];
                                index = i;
                        }
                }
                return index;
        }

}

int main()
{
        int a[10]={10,2,3,4,5,6,1,8,7,6};
	int r = rand()%100;
	printf("Trail Runs:%d\n",r);
	for (int i=0;i<r;i++)
	{	int x = rand()%10;
		search(a,10,x);
	}
	r = rand()%100;
	printf("Trail Runs:%d\n",r);
	for (int i=0;i<r;i++)
	{
		min(a,10);
	}

        return 0;
}
