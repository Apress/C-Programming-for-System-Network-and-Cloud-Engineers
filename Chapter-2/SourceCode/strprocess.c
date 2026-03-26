#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char inpStr[] = "Learn c at Apress";

	int N = strlen(inpStr);
	printf("Lenght of the string:%d\n", N);

	int i=0;
	while (inpStr[i]!='\0')
	{
		printf("%c",inpStr[i]);
		i++;
	}
	printf("\n");


	printf("%s\n",inpStr);

	char inpStr2[N+1];
	char inpStr3[N+1];
	strcpy(inpStr2,inpStr);
	printf("Same size copy:%s\n",inpStr2);
	
	strncpy(inpStr3,inpStr,10);
	printf("Specific length copy:%s\n",inpStr3);

	inpStr3[10]='\0';
	printf("Specific length copy with terminator:%s\n",inpStr3);

	char ext1[11] = "abcd";
	char ext2[] = "abcd";
	printf("%s\n", ext1);
	printf("%s\n", ext2);
	strcat(ext1,ext2);
	printf("%s\n", ext1);
	strncat(ext1,ext2,2);
	printf("%s\n", ext1);

	char * myPtr = strtok(inpStr, " ");
	while(myPtr != NULL) 
	{
	  	printf("%s\n",myPtr);
	 	myPtr = strtok(NULL, " ");
	}

	printf("ORIGINAL:%s\n",inpStr);
	printf("COPY:%s\n",inpStr2);

	inpStr2[N]='\0';
	i=0;
	while (inpStr2[i]!='\0')
	{
		printf("%c",inpStr2[i]);
		i++;
	}
	printf("\n");

	char *found = strstr(inpStr2, "c at");
  	if (found != NULL) 
	{
    		printf("Found string is copied: %s\n", found);
    		printf("ORIGINAL string is not changed: %s\n", inpStr2);
  	}
	char * found1 = strchr(inpStr2, 'c');

	char * found2 = strrchr(inpStr2, 'r');
	if (found1!=NULL)
		printf("Search From the Start:%s\n",found1);
	if (found2!=NULL)
		printf("Search From the Last:%s\n",found2);


	char *found3 = strpbrk(inpStr2, "Ars");
	if (found3 != NULL) 
	{
	  	printf("Some Character found from Ars at inpStr2 and from the character string is copied into found3:%s\n", found3);
	}

	found3 = strpbrk(inpStr2, "123");
	if (found3 != NULL) 
	{
	  	printf("Some Character found at:%s\n", found3);
	}
	else
	{
		printf("123 Characters are not found in:%s\n",inpStr2);
	}
    	printf("Original String: %s\n", inpStr2);
	
	int index = strspn(inpStr2, "Learn c at");
	printf("Length of the longest matching substring found in inpStr2 %d\n", index);

	index = strspn(inpStr2, "Learn b at");
	printf("Length of the longest matching substring found in inpStr2 %d\n", index);


	index = strspn(inpStr2, "Yearn c at");
	printf("Length of the longest matching substring found in inpStr2 %d\n", index);


}
