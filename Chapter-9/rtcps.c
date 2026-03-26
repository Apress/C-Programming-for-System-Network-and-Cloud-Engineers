#include <arpa/inet.h>  
#include <netinet/in.h> 
#include <stdio.h>      
#include <stdlib.h>    
#include <string.h>     
#include <sys/socket.h> 
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h>     
#include <netinet/tcp.h>
#include <errno.h>
#define BUF_SIZE 1024
#define PORT 12345
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

        int optval = 1;
	socklen_t optlen = sizeof(optval);
	if (setsockopt(tcp_ls, SOL_SOCKET, SO_REUSEADDR, &optval, optlen) < 0)
        {
                perror("setsockopt(SO_REUSEADDR) failed");
                exit(EXIT_FAILURE);
        }


        if (setsockopt(tcp_ls, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0)
        {
                perror("Error setting SO_KEEPALIVE");
                close(tcp_ls);
                exit(EXIT_FAILURE);
        }
        printf("SO_KEEPALIVE enabled.\n");

        optval = 10;
        if (setsockopt(tcp_ls, IPPROTO_TCP, TCP_KEEPIDLE, &optval, optlen) < 0)
        {
                perror("Error setting TCP_KEEPIDLE");
                close(tcp_ls);
                exit(EXIT_FAILURE);
        }
        printf("TCP_KEEPIDLE set to %d seconds.\n", optval);
        optval = 1;
        if (setsockopt(tcp_ls, IPPROTO_TCP, TCP_KEEPCNT, &optval, optlen) < 0)
        {
                perror("Error setting TCP_KEEPCNT");
                close(tcp_ls);
                exit(EXIT_FAILURE);
        }
        printf("TCP_KEEPCNT set to %d probes.\n", optval);

        optval = 1;
        if (setsockopt(tcp_ls, IPPROTO_TCP, TCP_KEEPINTVL, &optval, optlen) < 0)
        {
                perror("Error setting TCP_KEEPINTVL");
                close(tcp_ls);
                exit(EXIT_FAILURE);
        }
        printf("TCP_KEEPINTVL set to %d seconds.\n", optval);

    	bzero(&server, sizeof(server));
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(PORT);     

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
	printf("Parent PS server PID:%d\n",getpid());
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
	   
                if (fork()==0)
            	{

            		close(tcp_ls);

	     		fptr = fopen("sample.txt", "r");

    			if (fptr == NULL) 
			{
        			printf("Error: Could not open file.\n");
        			return 1; 
    			}

        		bzero(buf, BUF_SIZE);
        		ssize_t rcnt = recv(tcpc_cs, buf, sizeof(buf) - 1,0);
        		if (rcnt <= 0) 
			{
        			printf("Client disconnected or error occurred.\n");
        			continue;
        		}
        		buf[rcnt] = '\0'; 
        		printf("Client: %s %d\n",buf,rcnt);
			while (fread(buf,1, BUF_SIZE, fptr)>0) 
			{
				int sc;
    				sc=send(tcpc_cs, buf, strlen(buf),0);

    				if (errno==ECONNRESET) 
				{
        				perror("Peer closed the connection");
					exit(1);
    				}
    				printf("Sent: %s %d\n", buf, sc);
        		}


			printf("File closed\n");
	        	shutdown(tcpc_cs,SHUT_WR);
        		bzero(buf, BUF_SIZE);
                	ssize_t bytes_received = recv(tcpc_cs, buf, sizeof(buf), 0);
                	if (bytes_received == 0)
                	{
                        	printf("Client successfully read.\n");
                	}

			fclose(fptr);
		}
		else
		{
			close(tcpc_cs);
                  	int stat;
                  	waitpid(-1,&stat,WNOHANG);

		}
    
    	}

    	close(tcp_ls);

    	return 0;
}
