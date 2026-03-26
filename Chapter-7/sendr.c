#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct Message 
{
	long type;
    	char messg[200];
};

int main(void)
{
    	struct Message msg[5] = {{1,"A"}, {3,"B"},{3,"C"},{1,"D"},{2,"C"}};
    	int msqid;
  	key_t key;

    	if ((key = ftok("sendr.c", 'B')) == -1) 
	{
        	perror("ftok");
        	exit(1);
    	}

    	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) 
	{
        	perror("msgget");
        	exit(1);
    	}
    
	for (int i=0;i<5;i++)
	{

        	int len = strlen(msg[i].messg);
        	if (msgsnd(msqid, &msg[i], len, 0) == -1)
		{
            		perror("msgsnd");
		}
		else
		{
			printf("%s sent\n",msg[i].messg);
		}
    	}
    return 0;
}
