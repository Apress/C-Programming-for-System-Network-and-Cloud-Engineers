#include <arpa/inet.h>  // For inet_addr
#include <netinet/in.h> // For sockaddr_in
#include <stdio.h>      // For printf, perror
#include <stdlib.h>     // For exit
#include <string.h>     // For bzero
#include <sys/socket.h> // For socket, bind, listen, accept
#include <sys/types.h>  // For socket types
#include <sys/wait.h>  // For socket types
#include <unistd.h>     // For close
#include <netinet/tcp.h>
#define BUF_SIZE 10
#define PORT 12346

int main() 
{
    	int tcp_ls, tcp_cs;
    	struct sockaddr_in server, client;
    	socklen_t client_len;

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
    	server.sin_port = htons(PORT);     // Convert port to network byte order

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

    	client_len = sizeof(client);

    	while (1) 
	{
    		tcp_cs = accept(tcp_ls, (struct sockaddr *)&client, &client_len);
    		if (tcp_cs < 0) 
		{
        		perror("Accept failed");
        		close(tcp_ls);
        		exit(EXIT_FAILURE);
    		}
    		printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    		if (fork()==0)
    		{
	    		close(tcp_ls);
	     		fptr = fopen("sample2.txt", "r");

    			if (fptr == NULL) 
			{
        			printf("Error: Could not open file.\n");
        			return 1; // Indicate a	n error
    			}

        		while(1)
			{
        			bzero(buf, BUF_SIZE);
        			ssize_t rcnt = recv(tcp_cs, buf, sizeof(buf), 0);
        			if (rcnt <= 0) 
				{
            				printf("Client disconnected or error occurred.\n");
            				break;
        			}
        			buf[rcnt] = '\0'; 
        			printf("Client: %s\n", buf);

        			bzero(buf, BUF_SIZE);
				if (fread(buf,1, BUF_SIZE, fptr)>0) 
				{
    					if (send(tcp_cs, buf, strlen(buf), 0) == -1) 
					{
        					perror("Error sending data");
						break;	
    					}
    					printf("Sent: %s\n", buf);
					ssize_t rcnt = recv(tcp_cs, buf, sizeof(buf), 0);
					if (rcnt == 0)
                               		{
                                        	printf("Client disconnected or error occurred.\n");
                                        	break;
                                	}

        			}
				else
				{
					printf("File closed\n");
					fclose(fptr);
					exit(0);
				}
			}
     		}
    		else
     		{
			close(tcp_cs);
                  	int stat;
                  	waitpid(-1,&stat,WNOHANG);
     		} 
    
    	}

    	close(tcp_cs);
    	close(tcp_ls);

    	return 0;
}
