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
    	printf("Before Unshare the current process%d \n",getpid());
	system("ip a");

    	if (unshare(CLONE_NEWNET) == -1) 
	{
        	perror("unshare");
        	exit(EXIT_FAILURE);
    	}

    	printf("After Unshare the current process%d \n",getpid());
	system("ip a");

    return 0;
}
