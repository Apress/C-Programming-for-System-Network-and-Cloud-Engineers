#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
int main() 
{
	if (unshare(CLONE_NEWUSER) == -1)
        {
                perror("unshare");
                exit(EXIT_FAILURE);
        }

	pid_t ret=fork();
	if (ret==-1)
	{
		perror("fork");
		return 1;
	}
	if (ret==0)
	{	
		printf("Process 1 trying to read a test file with permissions 600 (others are not allowed)\n"); 
		const char *filename = "test.txt";
    		int fd;
    		ssize_t bytes_read;
		char buffer[1024];
		fd = open(filename, O_RDONLY);
		if (fd == -1) 
		{
	    		perror("Error opening file");
	    		return 1;
		}
		bytes_read = read(fd, buffer, 4);
		if (bytes_read == -1) 
		{
	    		perror("Error reading file");
	    		close(fd);
	    		return 1;
		}
		write(1, buffer, bytes_read);
		close(fd);
		exit(0);
	}    
	if (ret>0)
	{	
		waitpid(ret,NULL,0);
		printf("Process 2 trying to read a test file with permissions 6664 (others are  allowed)\n"); 
		const char *filename = "test2.txt";
                int fd;
                ssize_t bytes_read;
                char buffer[1024];
                fd = open(filename, O_RDONLY);
                if (fd == -1)
                {
                        perror("Error opening file");
                        return 1;
                }

		bytes_read = read(fd, buffer, 4);
		if (bytes_read == -1) 
		{
	    		perror("Error reading file");
	    		close(fd);
	    		return 1;
		}
		write(1, buffer, bytes_read);

		if (close(fd) == -1) 
		{
	    		perror("Error closing file");
	    		return 1;
		}

	}
    return 0;
}
