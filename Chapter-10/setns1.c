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

    	const char *exist_ns = argv[1];
    	int fd;

        printf("Before Unshare the current process%d \n",getpid());
	system("hostname");
    	fd = open(exist_ns, O_RDONLY | O_CLOEXEC);
    	if (fd == -1) 
    	{
        	perror("open");
        	exit(EXIT_FAILURE);
    	}

    	if (setns(fd, CLONE_NEWUTS) == -1) 
    	{
        	perror("setns");
        	close(fd);
        	exit(EXIT_FAILURE);
    	}

    	printf("Successfully the process %d attached with the existing namespace: %s\n", getpid(), exist_ns);
    	system("hostname");
	close(fd);
    	return 0;
}
