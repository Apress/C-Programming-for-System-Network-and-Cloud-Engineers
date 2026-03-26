#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void StrProcess1(char *p)
{
	int i;
	char a[10];
	strcpy(a,p);
	for (i=0;i<strlen(p);i++)
	{
		printf("String Access %c",a[i]);
	}

	printf("\n");
}
int main()
{
	char *p1; char *p2;
	p1=(char*)malloc(sizeof(char)*10);
	memset(p1,'a',10);
	StrProcess1(p1);
//	StrProcess1(p2);
	StrProcess1("abcdefghijk");

}
