#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sched.h>
#define KEY 7860
int main() 
{
  	int shmid;
  	int *shrdres;
  	int size = sizeof(int);
	pid_t pid;
  	shmid = shmget(KEY,size, 0666 | IPC_CREAT);
  	if (shmid == -1) 
  	{
    		perror("shmget failed");
    		return 1;
  	}
  	shrdres = (int *)shmat(shmid, NULL, 0);
  	if (shrdres == (int *)-1) 
  	{
   		perror("shmat failed");
    		return 1;
  	}
  	*shrdres=100;
	printf("Main Process ID:%d\n",getpid());
	printf("Main Process Successfully written sample contents into shared memory: %d \n",*shrdres);
 	/*if (unshare(CLONE_NEWIPC) == -1) 
	{
        	perror("unshare");
        	exit(EXIT_FAILURE);
    	}*/
  	pid = fork();
        if (pid == -1)
        {
                perror("fork failed");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
		shmid = shmget(KEY,size, 0666 | IPC_CREAT);
        	if (shmid == -1)
        	{
                	perror("shmget failed");
                	return 1;
        	}

  		shrdres = (int *)shmat(shmid, NULL, 0);
  		if (shrdres == (int *)-1) 
  		{
   			perror("shmat failed");
    			return 1;
  		}
		printf("%d Shared memory %d\n",getpid(),*shrdres);
                *shrdres = *shrdres+300;
		printf("%d Shared memory %d\n",getpid(),*shrdres);
  
                if (shmdt(shrdres) == -1)
                {
                        perror("shmdt");
                        exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
        }
	else if (pid>0)
	{
		wait(NULL);

		shmid = shmget(KEY,size, 0666 | IPC_CREAT);
                if (shmid == -1)
                {
                        perror("shmget failed");
                        return 1;
                }

  		shrdres = (int *)shmat(shmid, NULL, 0);
  		if (shrdres == (int *)-1) 
  		{
   			perror("shmat failed");
    			return 1;
  		}
		printf("%d Shared memory %d\n",getpid(),*shrdres);
                *shrdres = *shrdres+100;
		printf("%d Shared memory %d\n",getpid(),*shrdres);
                if (shmdt(shrdres) == -1)
                {
                        perror("shmdt");
                        exit(EXIT_FAILURE);
                }
		shmctl(shmid, IPC_RMID, NULL);
                exit(EXIT_SUCCESS);

	}
	return 0;
}
