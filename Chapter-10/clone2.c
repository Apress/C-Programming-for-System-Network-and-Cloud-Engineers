#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int child_process1(void *arg) 
{
   	printf("Child PID: %ld\n", (long)getpid());
	system("ip a");
    	return 0;
}


int main() 
{
    	char *stack1, *stack2;
    	char *stack_top1,*stack_top2;
    	pid_t child_pid1, child_pid2;

    	stack1 = malloc(1024 * 1024);
    	if (stack1 == NULL) 
    	{
        	perror("malloc");
        	exit(1);
    	}
    	stack_top1 = stack1 + (1024 * 1024); 


    	child_pid1 = clone(child_process1, stack_top1, CLONE_NEWPID | CLONE_NEWNET|SIGCHLD, NULL);
    	if (child_pid1 == -1) 
    	{
        	perror("clone");
        	exit(1);
    	}
    	printf("Parent PID: %ld\n", (long)getpid());
    	printf("Clone PID: %ld\n", (long)child_pid1);
    	waitpid(child_pid1, NULL, 0);


    	free(stack2);
    	return 0;
}
