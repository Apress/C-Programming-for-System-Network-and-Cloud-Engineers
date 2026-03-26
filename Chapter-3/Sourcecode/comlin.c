#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main()
{

	double time1, timedif;
        time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;

	char buf[10];
	printf("Hello library\n");
	strcpy(buf,"hello");
	memcpy(buf,"hello",5);
	double d;
	d=sqrt(10);
	printf("SQRT:%lf",d);
	 timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Second The elapsed time is %lf seconds\n", timedif);

}
