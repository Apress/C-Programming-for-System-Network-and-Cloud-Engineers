#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define INPQ "P1P2"
#define OUTQ "P2P3"
int main(void)
{
    	char s[300];
    	int num, fd1, fd2;

//    	mkfifo(INPQ, 0644);
    	mkfifo(OUTQ, 0644);

    	printf("P2 started to process P1 commands but it is waiting for P3 to be ready...\n");
    	fd1 = open(INPQ, O_RDONLY);
    	fd2 = open(OUTQ, O_WRONLY);
    	printf("P3 ready to receive...\n");
    	do 
	{
		if ((num = read(fd1, s, 300)) == -1)
		{
            		perror("read");
		}
        	else if (num>0)
		{
            		s[num] = '\0';
            		printf("P2: processed %d commnad: \"%s\"\n", num, s);
	    		int num1;
	    		if ((num1 = write(fd2, s, strlen(s))) == -1)
			{
                		perror("write");
			}
                	else
			{
                		printf("P2: send %d command to P3\n", num);
			}

        	}
    	}while (num > 0);
	close(fd1);
	close(fd2);
    return 0;
}
