#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> 

#define SRV_IP "127.0.0.1" 
#define SRV_PORT 12345
#define BUFFER_SIZE 1024     

int main() 
{
    	int ufd;
    	ssize_t scnt,rcnt;

    	struct sockaddr_in server;
    	char buffer[BUFFER_SIZE];
	socklen_t server_len = sizeof(server);
    	ufd = socket(AF_INET, SOCK_DGRAM, 0);

    	if (ufd < 0) 
	{
        	perror("Error creating socket");
        	exit(EXIT_FAILURE);
    	}

    	memset(&server, 0, sizeof(server));
    	server.sin_family = AF_INET;             
    	server.sin_port = htons(SRV_PORT);    

    	if (inet_pton(AF_INET, SRV_IP, &server.sin_addr) <= 0) 
	{
        	perror("Invalid address/ Address not supported");
        	close(ufd);
        	exit(EXIT_FAILURE);
    	}

	if (connect(ufd, (const struct sockaddr *)&server, sizeof(server)) < 0) 
	{
        	perror("connect failed");
        	exit(EXIT_FAILURE);
    	}

    	while(1)
    	{
    		char msg[100];
    		printf("Enter message");
    		scanf("%s",msg);
    		strcat(msg,"\n");
    		msg[strlen(msg)]='\0';
    		scnt = send(ufd, msg, strlen(msg), 0);
    		if (scnt < 0) 
		{
        		perror("Error sending message");
        		close(ufd);
        		exit(EXIT_FAILURE);
    		}
    		printf("Message sent: \"%s\" (%zd bytes)\n", msg, scnt);

    		server_len = sizeof(server);
    		rcnt = recv(ufd, buffer, BUFFER_SIZE - 1, 0);

    		printf("Rcvd from %s:%d\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

    		if (rcnt < 0) 
		{
        		perror("Error receiving response");
    		} 
		else if (rcnt == 0) 
		{
       	 		printf("Server closed connection or sent empty message.\n");
    		} 
		else 
		{
        		buffer[rcnt] = '\0';
        		printf("Response from server: \"%s\" (%zd bytes)\n", buffer, rcnt);
    		}
    	}	
    	close(ufd);
    	printf("Socket closed.\n");
    	return 0;
}
