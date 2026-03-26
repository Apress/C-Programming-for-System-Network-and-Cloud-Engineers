#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct Message 
{
	long type;
	char messg[200];
};
int gmqid;
void signal_handler(int signum)
{
        printf("Signal %d received \n", signum);

        if (signum == SIGINT)
        {
                printf("Process interrupted\n");
		msgctl(gmqid, IPC_RMID, NULL);
		exit(0);
        }

}

int main(void)
{
    	struct Message msg;
    	int msqid;
    	key_t key;
 	struct sigaction sa;
	sa.sa_handler = signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if (sigaction(SIGINT, &sa, NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }

    	if ((key = ftok("sendr.c", 'B')) == -1) 
	{
        	perror("ftok");
        	exit(1);
    	}
    	if ((msqid = msgget(key, 0644)) == -1) 
	{ 
        	perror("msgget");
        	exit(1);
    	}
	gmqid = msqid;
    
    	printf("Receiver Processing Messages in Priority.\n");

    	for(;;) 
	{ 
        
		while (msgrcv(msqid, &msg, sizeof msg.messg, 3, IPC_NOWAIT) != -1) 
		{
        		printf("Type-3: \"%s\"\n", msg.messg);
        	}
		while (msgrcv(msqid, &msg, sizeof msg.messg, 2, IPC_NOWAIT) != -1) 
		{
        		printf("Type-2: \"%s\"\n", msg.messg);
        	}
		while (msgrcv(msqid, &msg, sizeof msg.messg, 1, IPC_NOWAIT) != -1) 
		{
        		printf("Type-1: \"%s\"\n", msg.messg);
        	}
	}
	msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
