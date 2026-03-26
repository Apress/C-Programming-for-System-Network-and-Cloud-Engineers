#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#define SRV_PORT 12345
#define BUF_SIZE 1024

int main() 
{
    	int ufd,rcnt;
    	struct sockaddr_in server, client;
    	char buffer[BUF_SIZE];

    	if ((ufd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
        	perror("socket creation failed");
        	exit(EXIT_FAILURE);
    	}

	if (fcntl(ufd, F_SETFL, O_NONBLOCK) < 0) 
	{
        	perror("fcntl failed");
        	close(ufd);
        	exit(EXIT_FAILURE);
    	}
	int optval=1;
        if (setsockopt(ufd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0)
        {
                perror("setsockopt (SO_BROADCAST) failed");
                close(ufd);
                exit(EXIT_FAILURE);
	}
    	

    	memset(&server, 0, sizeof(server));
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_BROADCAST; 
   	server.sin_port = htons(SRV_PORT);
    	socklen_t len;
    	ssize_t mlen;

    	while (1) 
	{
		if (sendto(ufd,"Hello\n", strlen("Hello\n"), 0,
                        (struct sockaddr *)&server, sizeof(server)) < 0)
                {
                        perror("sendto failed");
                        close(ufd);
                        exit(EXIT_FAILURE);
                }
		printf("Message sent\n");
		socklen_t server_len = sizeof(client);
                rcnt = recvfrom(ufd, buffer, BUF_SIZE, 0,
                                        (struct sockaddr *)&client, &server_len);

                printf("Rcvd from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

                if (rcnt < 0)
                {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				sleep(1);
			}
			else
			{
                        	perror("Error receiving response");
                        	close(ufd);
                        	exit(EXIT_FAILURE);
			}
                }
                else
                {
                        buffer[rcnt] = '\0';
                        printf("Response from server: \"%s\" (%zd bytes)\n", buffer, rcnt);
			break;
		}


    	}

    	close(ufd);
    	return 0;
}
