#include<stdio.h>
#include<time.h>
int oneDarray(int a[], int n)
{
	int i;
	for (i=0;i<n;i++)
	{
		printf(" %d",a[i]);
	}
	printf("\n");
	printf("Size of array element a[0]: %ld",sizeof(*a));
	printf("\n");
}
int twoDarray(int a[][4], int n, int m)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
		{
			printf(" %d",a[i][j]);
		}
		printf("\n");
	}

	printf("\nSize of array element a[0]: %ld",sizeof(*a));
	printf("\nSize of inner  array element a[0][0] : %ld",sizeof(**a));
	printf("\n");
	a=a+1;
	for (j=0;j<m;j++)
        {
        	printf(" %d",a[0][j]);
        }


}
int arrayAccess(int a[1024][1024])
{
	double time1, timedif;

        time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;

	for (int i=0;i<1024; i++)
	{
		for (int j=0;j<1024;j++)
		{
			a[i][j]=i;
		}
	}
	timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Row Access The elapsed time is %lf seconds\n", timedif);

        time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;

	for (int i=0;i<1024; i++)
	{
                for (int j=0;j<1024;j++)
                {
                        a[j][i]=i;
                }
        }
	timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Column access The elapsed time is %lf seconds\n", timedif);


}
int arraySizeBasedAccess()
{
	int a[2048];
	int b[8];
        double time1, timedif;
        time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;
        for (int i=0;i<2048; i++)
        {
                for (int j=0;j<8;j++)
                {
                        if (a[i]==b[j])
				;
                }
        }
        timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Inner loop smaller size Access The elapsed time is %lf seconds\n", timedif);

	time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;
        for (int i=0;i<8; i++)
        {
                for (int j=0;j<2048;j++)
                {
                        if (a[i]==b[j])
                                ;
                }
        }
        timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Inner loop larger size Access The elapsed time is %lf seconds\n", timedif);


}


int variableSize(int n)
{
	int a[n];
	for (int i=0;i<n;i++)
	{
		a[i]=0;
	}
	printf("Array dynamic size is:%d successfully allocated and initialized ",n);
}


int threeDarray(int a[][2][2], int n, int m, int l)
{
	int i,j,k;
        for (i=0;i<n;i++)
        {
                for (j=0;j<m;j++)
                {
			for (k=0;k<l;k++)
			{
                        	printf(" %d",a[i][j][k]);
			}
                	printf("\n");
                }
                printf("\n");
        }

	printf("\nSize of array element a[0]: %ld",sizeof(*a));
	printf("\nSize of inner  array element a[0][0]: %ld",sizeof(**a));
	printf("\nSize of inner inner  array element a[0][0][0]: %ld",sizeof(***a));
	printf("\n");
	a=a+1;
        for (j=0;j<m;j++)
        {
                for (k=0;k<l;k++)
                {

                	printf(" %d",a[0][j][k]);

                }
                printf("\n");
        }
        printf("\n");



}

int main()
{
	int a[8] = {1,2,3,4,5,6,7,8};
	int b[2][4] = {{1,2,3,4},{5,6,7,8}};
	int c[2][2][2] = {{{1,2},{3,4}},{{5,6},{7,8}}};
	int d[2][2][2][2] = {{{{1,2},{3,4}},{{5,6},{7,8}}},{{{9,10},{11,12}},{{13,14},{15,16}}}};
	oneDarray(a,8);
	twoDarray(b,2,4);
	threeDarray(c,2,2,2);
	int e[1024][1024];
	arrayAccess(e);
	arraySizeBasedAccess();
	variableSize(1024);
	variableSize(10);



}
