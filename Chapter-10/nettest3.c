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
	char hostname[256];
        int result = gethostname(hostname, sizeof(hostname));
        printf("Before Unshare the current process%d hostname %s\n",getpid(), hostname);

        if (unshare(CLONE_NEWUTS) == -1)
        {
                perror("unshare");
                exit(EXIT_FAILURE);
        }


	pid_t pid;
  	pid = fork();
        if (pid == -1)
        {
                perror("fork failed");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {

        	system("hostname newname");
        	result = gethostname(hostname, sizeof(hostname));
        	printf("After Unshare the current process%d hostname %s\n",getpid(), hostname);

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
		system("echo -e 'HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!' |nc -lp 9090");
		
//                exit(EXIT_SUCCESS);
        }
	else if (pid>0)
	{
		wait(NULL);
	}

	return 0;
}
