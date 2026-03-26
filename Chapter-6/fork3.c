#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
	int ncp = 3;
    	pid_t cpids[ncp];
    	int i;
	char *cmds[][10] = {{"/bin/ls","-l",NULL},{"/bin/ps","-a",NULL},{"/bin/df","-h",NULL}};


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
			execvp(cmds[i][0],cmds[i]);
			perror("execvp");	
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
