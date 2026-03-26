#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void asr()
{
	//sudo sysctl -w kernel.randomize_va_space=2
	int *p;
	p=(int*)malloc(sizeof(int)*100);
	printf("Address:%p\n",p);
	int a;
	int b;
	printf("Address:%p\n",&a);
	printf("Address:%p\n",&b);
}
void stackguard(char *buffer1)
{

//	readelf -W -s ./a.out | grep -i _stack_chk_fail
	char buffer2[4];
	strcpy(buffer2,buffer1);
	sprintf(buffer2,"%s",buffer1);
	memcpy(buffer2,buffer1,5);
}

void strfortify(char *buffer1)
{

//	gcc security.c -O2

        char buffer2[4];
        strcpy(buffer2,buffer1);
}
void printfortify(char *buffer1)
{

        char buffer2[4];
        sprintf(buffer2,"%s",buffer1);
}
void memfortify(char *buffer1)
{

        char buffer2[4];
        memcpy(buffer2,buffer1,5);
}

void stackexec(int i,int j)
{

	int g(int a,int b)
	{
		return a+b;
	}

	int h(int a,int b)
	{
		return a-b;
	}
	int (*p)(int,int);
	p=&g;
	printf("%d",p(i,j));
	p=&h;
	printf("%d",p(i,j));

}
void nostackexec(int i,int j)
{

	int g(int a,int b)
	{
		return a+b;
	}

	int h(int a,int b)
	{
		return a-b;
	}
	printf("%d",g(i,j));
	printf("%d",h(i,j));

}
int main()
{
//	asr();
//	stackguard("abcdef");
//	strfortify("abcdef");
//	printfortify("abcdef");
//	memfortify("abcdef");
//	stackexec(40,30);
//	nostackexec(40,30);

}
