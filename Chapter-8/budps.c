#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SRV_PORT 12345
#define BUF_SIZE 1024

int main() 
{
    	int ufd;
    	struct sockaddr_in server, client;
    	char buffer[BUF_SIZE];

    	if ((ufd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
        	perror("socket creation failed");
        	exit(EXIT_FAILURE);
    	}

    	memset(&server, 0, sizeof(server));
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY; 
    	server.sin_port = htons(SRV_PORT);

    	if (bind(ufd, (const struct sockaddr *)&server, sizeof(server)) < 0) 
	{
        	perror("bind failed");
        	exit(EXIT_FAILURE);
    	}

    	printf("UDP Server listening on port %d...\n", SRV_PORT);

    	socklen_t len;
    	ssize_t mlen;

    	while (1) 
	{
        	len = sizeof(client);
        	mlen = recvfrom(ufd, (char *)buffer, BUF_SIZE - 1, 0,
                     	(struct sockaddr *)&client, &len);
        	if (mlen < 0) 
		{
            		perror("recvfrom failed");
            		exit(EXIT_FAILURE);
        	}
        	buffer[mlen] = '\0';

        	printf("Client message from %s:%d: %s\n",
               	inet_ntoa(client.sin_addr), ntohs(client.sin_port), buffer);
		char msg[BUF_SIZE];
        
		printf("Enter Server Message\n");
		scanf("%s",msg);
		strcat(msg,"\n");
		msg[strlen(msg)]='\0';
       	 	sendto(ufd, (const char *)msg, strlen(msg), 0,
               		(const struct sockaddr *)&client, len);
    	}

    	close(ufd);
    	return 0;
}
