#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MEM_CGROUP_DIR "/sys/fs/cgroup/memory/mymgrp"
#define MEM_CGROUP_PS "/sys/fs/cgroup/memory/mymgrp/cgroup.procs"
#define MEM_LIMIT "/sys/fs/cgroup/memory/mymgrp/memory.limit_in_bytes"
#define MEM_USAGE "/sys/fs/cgroup/memory/mymgrp/memory.max_usage_in_bytes"
int main() 
{
	rmdir(MEM_CGROUP_DIR);
    	for (int i=0;i<3;i++)
    	{
		pid_t pid1 = fork();
		if (pid1==0)
		{
    			pid_t pid = getpid();
    			int fd;
    			if (mkdir(MEM_CGROUP_DIR, 0755) == -1) 
			{
        			perror("Error creating cgroup directory (may already exist)");
    			}
    			fd = open(MEM_CGROUP_PS, O_WRONLY | O_APPEND);
    			if (fd == -1) 
			{
        			perror("Error opening cgroup.procs");
        			return EXIT_FAILURE;
    			}
    			dprintf(fd, "%d\n", pid);
    			close(fd);

    			fd = open(MEM_LIMIT, O_WRONLY);
    			if (fd == -1) 
			{
        			perror("Error opening memory limit file");
        			return EXIT_FAILURE;
    			}
    			unsigned int cl = 1;
    			dprintf(fd, "%dM\n", cl); // 
    			close(fd);

    			printf("Running an infinite loop to consume CPU...\n");
    			while (1) 
			{
				int *p=malloc(sizeof(int)*250);
				system("cat /sys/fs/cgroup/memory/mymgrp/memory.max_usage_in_bytes");
    			}
		}
    	}
    	return EXIT_SUCCESS;
}
