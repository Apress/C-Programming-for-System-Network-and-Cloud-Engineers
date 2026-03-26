#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_COMMANDS 10
int main() 
{
    	char *cmds[MAX_COMMANDS][100] = {{"cat", "ncmdschain.c", "ncmdschain.c",NULL}, {"grep", "fork", NULL}, {"wc", "-l", NULL}, {NULL}};
    	int noc = 3;
    	int pipes[noc-1][2];
    	pid_t cpids[noc];

    	for (int i=0; i<noc-1; i++) 
    	{
        	if (pipe(pipes[i]) == -1) 
		{
            		perror("pipe");
            		exit(EXIT_FAILURE);
        	}
    	}

    	for (int i=0; i<noc; i++) 
    	{
        	cpids[i] = fork();
        	if (cpids[i] == -1) 
		{
            		perror("fork");
            		exit(EXIT_FAILURE);
        	}

        	if (cpids[i] == 0) 
		{ 
            		if (i == 0) 
	    		{
                		dup2(pipes[i][1], STDOUT_FILENO); 
            		}
            		else if (i>0 && i<noc-1)
	    		{
                		dup2(pipes[i-1][0], STDIN_FILENO); 
                		dup2(pipes[i][1], STDOUT_FILENO); 
            		}
            		else if (i == noc-1) 
	    		{
                		dup2(pipes[i-1][0], STDIN_FILENO); 
            		}
    	    		for (int j=0; j<noc-1; j++) 
    	    		{
        			close(pipes[j][0]);
        			close(pipes[j][1]);
    	    		}

	    		execvp(cmds[i][0], cmds[i]);
            		perror("execvp");
            		exit(EXIT_FAILURE);
        	}
    	}

    	for (int i=0; i<noc-1; i++) 
    	{
        	close(pipes[i][0]);
        	close(pipes[i][1]);
    	}
    	for (int i=0; i<noc; i++) 
    	{
        	wait(NULL);
    	}

    	return 0;
}
