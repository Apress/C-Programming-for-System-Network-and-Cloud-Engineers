#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
	int ncp = 3;
    	pid_t cpids[ncp];
    	int i;

    	for (i=0;i<ncp;i++) 
	{
        	cpids[i] = fork();
        	if (cpids[i]<0) 
		{
            		perror("fork");
            		return 1;
        	} 
		else if (cpids[i]==0) 
		{
			for (int j=0;j<20;j++)
			{
            			printf("Child process %d (PID: %d) generating: %d\n", i+1, getpid(),j);
			
			}
            		printf("Child process %d (PID: %d) done\n", i + 1, getpid());
            		exit(0); 
        	}
    	}	

   	printf("Parent process (PID: %d) waiting for children...\n", getpid());
    	for (i = 0;i<ncp;i++) 
	{
        	int status;
        	pid_t pid = wait(&status);
        	if (pid==-1) 
		{
            		perror("wait");
            		return 1;
        	}	
        	if (WIFEXITED(status)) 
		{
           		printf(" Child process %d exit status %d\n", pid,WEXITSTATUS(status));
        	} 
		else if (WIFSIGNALED(status)) 
		{
            		printf(" Child process %d existed due to signal %d\n",pid,WTERMSIG(status));
       	 	}

    	}
    	printf("Parent process (PID: %d) Done\n", getpid());
   	return 0;
}
