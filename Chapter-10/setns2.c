#define _GNU_SOURCE // Required for setns()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h> 
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) 
{

    	const char *exist_ns1 = argv[1];
    	const char *exist_ns2 = argv[2];
    	int fd1,fd2;

        printf("Before Unshare the current process%d \n",getpid());
	system("ip a");
	system("id");
    	fd1 = open(exist_ns1, O_RDONLY | O_CLOEXEC);
    	if (fd1 == -1) 
    	{
        	perror("open");
        	exit(EXIT_FAILURE);
    	}

    	if (setns(fd1, CLONE_NEWNET) == -1) 
    	{
        	perror("setns");
        	close(fd1);
        	exit(EXIT_FAILURE);
    	}

	fd2 = open(exist_ns2, O_RDONLY | O_CLOEXEC);
        if (fd2 == -1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }

        if (setns(fd2, CLONE_NEWUSER) == -1)      
        {
                perror("setns");
                close(fd2);
                exit(EXIT_FAILURE);
        }

    	printf("Successfully the process %d attached with the existing namespaces: %s %s\n", getpid(), exist_ns1, exist_ns2);
    	system("ip a");
    	system("id");
	close(fd1);
	close(fd2);
    	return 0;
}
