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
    	printf("Before Unshare the current process%d uid %d\n",getpid(), getuid());

    	if (unshare(CLONE_NEWUSER) == -1) 
	{
        	perror("unshare");
        	exit(EXIT_FAILURE);
    	}

    	printf("After Unshare the current process%d uid %d\n",getpid(), getuid());

    return 0;
}
