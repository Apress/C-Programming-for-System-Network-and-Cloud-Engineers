#define _GNU_SOURCE
#include <sched.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
 	char hostname[256];
    	int result = gethostname(hostname, sizeof(hostname));
    	printf("Before Unshare the current process%d hostname %s\n",getpid(), hostname);

    	if (unshare(CLONE_NEWUTS) == -1) 
	{
        	perror("unshare");
        	exit(EXIT_FAILURE);
    	}

	system("hostname newname");
    	result = gethostname(hostname, sizeof(hostname));
    	printf("After Unshare the current process%d hostname %s\n",getpid(), hostname);

    return 0;
}
