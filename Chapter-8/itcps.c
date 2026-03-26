#include <arpa/inet.h>  
#include <netinet/in.h> 
#include <stdio.h>  	
#include <stdlib.h> 	
#include <string.h> 	
#include <sys/socket.h> 
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h> 	
#define BUF_SIZE 10
#define PORT 12346

int main()
{
    	int tcp_ls, tcpc_cs;
    	struct sockaddr_in server, client;
    	socklen_t slen;
    	FILE *fptr;
    	char buf[BUF_SIZE];
    	tcp_ls = socket(AF_INET, SOCK_STREAM, 0);
    	if (tcp_ls < 0)
    	{
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
    	}
    	bzero(&server, sizeof(server));
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces
    	server.sin_port = htons(PORT); 	// Convert port to network byte order
    	if (bind(tcp_ls, (const struct sockaddr *)&server, sizeof(server)) < 0)
    	{
            perror("Socket binding failed");
            close(tcp_ls);
            exit(EXIT_FAILURE);
    	}
    	if (listen(tcp_ls, 10) < 0)
    	{
            perror("Listen failed");
            close(tcp_ls);
            exit(EXIT_FAILURE);
    	}
    	printf("Server listening on port %d...\n", PORT);
    	slen = sizeof(client);
    	while (1)
    	{
		tcpc_cs = accept(tcp_ls, (struct sockaddr *)&client, &slen);
		if (tcpc_cs < 0)
		{
			perror("Accept failed");
			close(tcp_ls);
                  	exit(EXIT_FAILURE);
            	}
            	printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            	fptr = fopen("sample.txt", "r");

		if (fptr == NULL)
		{
			printf("Error: Could not open file.\n");
                 	 return 1; 
		}	

            	while(1)
		{
			bzero(buf, BUF_SIZE);
                  	ssize_t rcnt = recv(tcpc_cs, buf, sizeof(buf), 0);
			if (rcnt <= 0)
			{
				printf("Client disconnected or error occurred.\n");
				break;
			}
			buf[rcnt] = '\0'; // Null-terminate the received data
			printf("Client: %s\n", buf);
			bzero(buf, BUF_SIZE);
            		if (fread(buf,1, BUF_SIZE, fptr)>0)
                  	{
				if (send(tcpc_cs, buf, strlen(buf), 0) == -1)
				{
                        		perror("Error sending data");
					break;
				}
				printf("Sent: %s\n", buf);
			}
                  	else
			{
				printf("File closed\n");
                        	fclose(fptr);
                  	}
            	}
   	}
	close(tcpc_cs);
    	close(tcp_ls);
    	return 0;
}

