#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
void signal_handler(int signum)
{
        printf("Signal %d received by process %d\n", signum, getpid());
        if (signum == SIGTERM)
        {
                printf("Process interrupted\n");
        }

        if (signum == SIGINT)
        {
                printf("Process interrupted\n");
        }
        if (signum == SIGPIPE)
        {
                printf("Pipe error\n");
        }
        if (signum == SIGSEGV)
        {
                printf("Process segfault handled\n");
		exit(1);
        }

}

int main()
{
	int *p;
	struct sigaction sa;
        sa.sa_handler = signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if (sigaction(SIGSEGV, &sa, NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }
        if (sigaction(SIGINT, &sa, NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }

        if (sigaction(SIGTERM, &sa, NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }

        if (sigaction(SIGPIPE, &sa, NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }
    	pid_t ret;
	ret = fork();
	if (ret<0)
	{
		perror("fork failed");
	}
	if (ret==0)
	{
		kill(getpid(),SIGPIPE);
		//*p=300;
		char *cmd[] = {"ps", "-a", NULL};
		execvp(cmd[0],cmd);
		perror("execvp");
                exit(EXIT_FAILURE);

	}	
	if (ret>0)
	{
		int stat;
		printf("Parent process\n");

		kill(getpid(),SIGTERM);
		char *cmd[] = {"ls", "-l", NULL};
    		pid_t cpid;
		cpid=waitpid(ret,&stat,0);
		if (cpid==-1)
                {
                        perror("wait");
                        return 1;
                }
                if (WIFEXITED(stat))
                {
                        printf(" Child process %d exit status %d\n", cpid,WEXITSTATUS(stat));
                }
		execvp(cmd[0],cmd);
		perror("execvp");
                exit(EXIT_FAILURE);

	}

}

