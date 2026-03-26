#include<stdio.h>
#include<time.h>
void array2()
{
	int a[2][4]={{1,2,3,4},{5,6,7,8}};
	int (*p)[4];
	p=&a[0];	
	for (int i=0;i<2;i++)
	{
		printf("%d ",(*p)[0]);
		printf("%d ",(*p)[1]);
		printf("%d ",(*p)[2]);
		printf("%d ",(*p)[3]);
		printf("\n");

		p=p+1;
	}
	
}


void array3()
{
        int a[4][2][2]={{{1,2},{3,4}},{{5,6},{7,8}},{{9,10},{11,12}},{{13,14},{15,16}}};
        int (*p)[2][2];
        p=&a[0];
        for (int i=0;i<4;i++)
        {
		printf("%d ",(*p)[0][0]);
		printf("%d ",(*p)[0][1]);
		printf("\n");
		printf("%d ",(*p)[1][0]);
		printf("%d ",(*p)[1][1]);
		printf("\n");
                p=p+1;
        }

}

void array1()
{
	int a[2048];
	double time1, timedif;
        time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;


	for (int i=0;i<2048;i++)
	{
		a[i]=i;
		a[i]=a[i]+1;
	}
        timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Arrays The elapsed time is %lf seconds\n", timedif);

	time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;


	int *p=a;
	for (int i=0;i<2048;i++)
        {
		*p=i;
		*p=*p+1;
		p++;
        }

        timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Pointers The elapsed time is %lf seconds\n", timedif);
}
int main()
{
	array1();
	array2();
	array3();
}


