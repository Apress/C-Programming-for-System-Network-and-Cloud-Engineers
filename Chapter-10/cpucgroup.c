#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CPU_CGROUP_DIR "/sys/fs/cgroup/cpu/mycgrp"
#define CPU_CGROUP_PS "/sys/fs/cgroup/cpu/mycgrp/cgroup.procs"
#define CPU_QUOTA "/sys/fs/cgroup/cpu/mycgrp/cpu.cfs_quota_us"
#define CPU_PERIOD "/sys/fs/cgroup/cpu/mycgrp/cpu.cfs_period_us"

int main() 
{
	rmdir(CPU_CGROUP_DIR);
    	for (int i=0;i<5;i++)
    	{
		pid_t pid1 = fork();
		if (pid1==0)
		{

    			pid_t pid = getpid();
    			int fd;

    			if (mkdir(CPU_CGROUP_DIR, 0755) == -1) 
			{
        			perror("Error creating cgroup directory (may already exist)");
    			}

    			fd = open(CPU_CGROUP_PS, O_WRONLY | O_APPEND);
    			if (fd == -1) 
			{
        			perror("Error opening cgroup.procs");
        			return EXIT_FAILURE;
    			}
    			dprintf(fd, "%d\n", pid);
    			close(fd);

    			fd = open(CPU_QUOTA, O_WRONLY);
    			if (fd == -1) 
			{
        			perror("Error opening cpu.cfs_quota_us");
        			return EXIT_FAILURE;
    			}
    			unsigned int cl = 1000;
    			dprintf(fd, "%d\n", cl); // 1ms quota
    			close(fd);

    			fd = open(CPU_PERIOD, O_WRONLY);
    			if (fd == -1) 
			{
        			perror("Error opening cpu.cfs_period_us");
        			return EXIT_FAILURE;
    			}
    			dprintf(fd, "%d\n", 10000); // 10ms period
    			close(fd);
    			printf("Running an infinite loop to consume CPU...\n");
    			while (1) 
			{
    			}
		}
    	}
    	return EXIT_SUCCESS;
}
