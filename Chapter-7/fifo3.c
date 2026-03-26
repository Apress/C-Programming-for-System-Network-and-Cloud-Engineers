#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define INPQ "P2P3"
int main(void)
{
    	char s[300];
    	int num, fd1;

    	printf("P3 waiting for P2 commands...\n");
    	fd1 = open(INPQ, O_RDONLY);
    	printf("P3 can receive P2 commands...\n");
    	do 
	{
		if ((num = read(fd1, s, 300)) == -1)
		{
            		perror("read");
		}
        	else if (num>0)
		{
            		s[num] = '\0';
            		printf("P3: executed the commands of P2 %d : \"%s\"\n", num, s);
        	}
    	}while (num > 0);
	close(fd1);

    return 0;
}
