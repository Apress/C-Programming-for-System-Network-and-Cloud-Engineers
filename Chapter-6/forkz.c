#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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
		exit(0);

	}	
	if (ret>0)
	{
		int stat;
		sleep(3);
		printf("Parent process\n");
	}
	printf("Task to be done\n");

}

