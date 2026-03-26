#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define OUTQ "P1P2"
int main(void)
{
    	char s[300];
    	int num, fd;

	mkfifo(OUTQ, 0644);

    	printf("P1 waiting for P2\n");
    	fd = open(OUTQ, O_WRONLY);
    	printf("P2 ready then sending commands\n");
    	char *str[3] = {"READ", "COMPRESS", "SEND"}; 		
	for (int i=0;i<3;i++)
     	{
        	if ((num = write(fd, str[i], strlen(str[i]))) == -1)
		{
            		perror("write");
		}
        	else
		{
            		printf("P1: Command %d size in bytes\n", num);
		}
    	}
	close(fd);
    return 0;
}
