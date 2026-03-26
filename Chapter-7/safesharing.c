#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <semaphore.h>
#define KEY 3333
int main() 
{
  	pid_t pid;
  	int shmid;
  	int *shrdres;
  	int size = sizeof(int);
  	sem_t *semkey = sem_open("/mysemlock", O_CREAT | O_EXCL, 0644, 1);
    	if (semkey == SEM_FAILED) 
    	{
        	perror("sem_open failed");
        	exit(EXIT_FAILURE);
    	} 

  	shmid = shmget(KEY, size, 0666 | IPC_CREAT);
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

  	for (int i = 0; i < 10; i++) 
  	{
        	pid = fork();
        	if (pid == -1) 
		{
            		perror("fork failed");
            		exit(EXIT_FAILURE);
        	} 
		else if (pid == 0) 
		{
            		
			sem_wait(semkey); 
            		for(int k=0;k<10000;k++)
  	    			*shrdres = *shrdres+1;
            		sem_post(semkey); 
			if (shmdt(shrdres) == -1)
                        {
                                perror("shmdt");
                                exit(EXIT_FAILURE);
                        }

            		exit(EXIT_SUCCESS);
        	}
    	}

    	for (int i = 0; i < 10; i++) 
    	{
        	wait(NULL);
    	}

    	printf("Final shared variable value: %d\n", *shrdres);

  	sem_close(semkey); // Close the semaphore
        sem_unlink("/mysemlock"); // Remove the se
	if (shmdt(shrdres) == -1)
        {
        	perror("shmdt");
                exit(EXIT_FAILURE);
        }
	shmctl(shmid, IPC_RMID, NULL);
  	return 0;
}
