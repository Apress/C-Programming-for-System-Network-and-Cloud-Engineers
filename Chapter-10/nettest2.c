#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sched.h>
int main() 
{
	pid_t pid;
  	pid = fork();
        if (pid == -1)
        {
                perror("fork failed");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
    		int fd;

    		fd = open("/var/run/netns/c3ns", O_RDONLY | O_CLOEXEC);
    		if (fd == -1) 
		{
        		perror("open");
        		exit(EXIT_FAILURE);
    		}

    		if (setns(fd, CLONE_NEWNET) == -1) 
		{
        		perror("setns");
        		close(fd);
        		exit(EXIT_FAILURE);
    		}

		system("ip a");
		system("nc -l 1234");
		
//                exit(EXIT_SUCCESS);
        }
	else if (pid>0)
	{
		wait(NULL);
	}

	return 0;
}
