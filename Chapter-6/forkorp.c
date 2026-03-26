#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    	pid_t ret;
	ret = fork();
	if (ret<0)
	{
		perror("fork failed");
	}
	if (ret==0)
	{
		printf("child process created %d\n",getpid());
		printf("child process parent %d\n",getppid());
		sleep(4);
		printf("orphan process parent %d\n",getppid());
		exit(0);

	}	
	if (ret>0)
	{
		printf("Parent process%d\n",getpid());
		sleep(1);
		exit(0);
	}

}

