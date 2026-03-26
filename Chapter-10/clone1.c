#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int process1(void *arg) 
{
   	printf("Child PID: %ld\n", (long)getpid());
	system("ip a");
    	return 0;
}

static int process2(void *arg)
{
        printf("Child PID: %ld\n", (long)getpid());
	system("ip a");
        return 0;
}



int main() 
{
    	char *stm1, *stm2;
    	char *tos1,*tos2;
    	pid_t pid1, pid2;

    	stm1 = malloc(1024 * 1024);
    	if (stm1 == NULL) 
    	{
        	perror("malloc");
        	exit(1);
    	}
    	tos1 = stm1 + (1024 * 1024); 

	stm2 = malloc(1024 * 1024);
        if (stm2 == NULL)
        {
                perror("malloc");
                exit(1);
        }
        tos2 = stm2 + (1024 * 1024);



    	pid1 = clone(process1, tos1, CLONE_NEWPID | SIGCHLD, NULL);
    	if (pid1 == -1) 
    	{
        	perror("clone");
        	exit(1);
    	}
    	printf("Parent PID: %ld\n", (long)getpid());
    	printf("Clone PID: %ld\n", (long)pid1);
    	waitpid(pid1, NULL, 0);


	pid2 = clone(process2, tos2, CLONE_NEWNET | SIGCHLD, NULL);
        if (pid2 == -1)
        {
                perror("clone");
                exit(1);
        }
        printf("Parent PID: %ld\n", (long)getpid());
        printf("Clone PID: %ld\n", (long)pid2);
        waitpid(pid2, NULL, 0);



    	free(stm1);
    	free(stm2);
    	return 0;
}
