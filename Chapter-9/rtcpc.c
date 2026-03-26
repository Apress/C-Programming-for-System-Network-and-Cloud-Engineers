#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>


#define PORT_NUMBER 12345
#define SERVER_IP_ADDRESS "127.0.0.1"
#define BUF_SIZE 1024

int main() 
{
    	int tcp_cs;
    	struct sockaddr_in server_address;
    	
	FILE *fptr;
    	char buf[BUF_SIZE]; 

    	fptr = fopen("sample.txt", "r");
    	if (fptr == NULL) 
	{
        	printf("Error: Could not open file.\n");
        	return 1; // Indicate an error
    	}
    	tcp_cs = socket(AF_INET, SOCK_STREAM, 0);
    	if (tcp_cs == -1) 
	{
        	perror("Error creating socket");
        eed grant equipment BIDs technical evaluation	exit(EXIT_FAILURE);
    	}

    	server_address.sin_family = AF_INET;
    	server_address.sin_port = htons(PORT_NUMBER);
    	server_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

    	if (connect(tcp_cs, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) 
	{
        	perror("Error connecting to server");
        	exit(EXIT_FAILURE);
    	}
    	printf("Connected to server %s:%d\n", SERVER_IP_ADDRESS, PORT_NUMBER);
	printf("Enter sample text\n");
	scanf("%s",buf);

    	if (send(tcp_cs, buf, strlen(buf), 0) == -1) 
	{
		perror("Error sending data");
		exit(EXIT_FAILURE);
	}
	printf("Sent: %s\n", buf);
	while(1)
	{
		

		ssize_t rcnt = recv(tcp_cs, buf, sizeof(buf) - 1, 0);

		if (rcnt == -1) 
		{
			perror("Error receiving data");
			exit(EXIT_FAILURE);
		}
		if (rcnt == 0) 
		{
			perror("closing connection");
			break;
		}

		buf[rcnt] = '\0';
		printf("Received: %s %d\n", buf,rcnt);


	}
    
    	close(tcp_cs);

    return 0;
}

