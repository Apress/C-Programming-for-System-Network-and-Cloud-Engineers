#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int global=100;
int main()
{
    	pid_t ret;
	ret = fork();
	int local=200;
	int *p=(int*)malloc(sizeof(int));
	*p=300;
	if (ret<0)
	{
		perror("fork failed");
	}
	if (ret==0)
	{
		printf("child process created %d\n",getpid());
		printf("Parent process id %d\n",getppid());
		printf("Parent copy global %d\n",global);
		printf("Parent copy local %d\n",local);
		global=100*10;
		local=local*10;
		*p=600;
		printf("Child copy global %d\n",global);
		printf("Child copy local %d\n",local);
		printf("Child heap copy %d\n",*p);
		free(p);
		exit(0);

	}	
	if (ret>0)
	{
		int stat;
		printf("Parent process\n");

		printf("Inside Parent copy global %d\n",global);
		printf("Inside Parent copy local %d\n",local);
		global=100*5;
		local=local*5;
		*p=800;
		printf("Inside Parent copy global %d\n",global);
		printf("Inside Parent copy local %d\n",local);
		printf("Inside Parent heap copy %d\n",*p);
    		pid_t cpid;
		cpid=waitpid(ret,&stat,0);
		if (cpid==-1)
                {
                        perror("wait");
                        return 1;
                }
                if (WIFEXITED(stat))
                {
                        printf(" Child process %d exit status %d\n", cpid,WEXITSTATUS(stat));
                }
		free(p);


	}
	printf("Task to be done\n");

}

