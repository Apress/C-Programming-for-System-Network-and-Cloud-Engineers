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

    		fd = open("/var/run/netns/c4ns", O_RDONLY | O_CLOEXEC);
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
		system("ping -c3 192.168.27.10");
                exit(EXIT_SUCCESS);
        }
	else if (pid>0)
	{
		wait(NULL);

		int fd;

                fd = open("/var/run/netns/c5ns", O_RDONLY | O_CLOEXEC);
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
		system("ping -c3 192.168.26.10");
                exit(EXIT_SUCCESS);

	}
	return 0;
}
