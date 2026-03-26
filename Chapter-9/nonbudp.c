#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<errno.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>


#define UDP_PORT 12345
#define MAX_BUFFER_SIZE 1024

int block2nonblock(int udp_bsd)
{
    int flags = fcntl(udp_bsd, F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl(F_GETFL)");
        return -1;
    }

    if (fcntl(udp_bsd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl(F_SETFL)");
        return -1;
    }
    return 0;
}


int main() 
{
    int uds[2];
    struct sockaddr_in udp_server_addr[2], client_addr[2];
    socklen_t client_addr_len = sizeof(client_addr[0]);
    char buf1[MAX_BUFFER_SIZE];
    char buf2[MAX_BUFFER_SIZE];
    int maxsd, rval;
    fd_set rfds;

    for (int i=0;i<2;i++)
    {
    	uds[i] = socket(AF_INET, SOCK_DGRAM, 0);
    	if (uds[i] < 0) 
    	{
        	perror("UDP socket creation failed");
        	exit(EXIT_FAILURE);
    	}
	if (block2nonblock(uds[i]) < 0)
        { 
           	close(uds[i]); exit(EXIT_FAILURE);  
        }
        

    	memset(&udp_server_addr[i], 0, sizeof(udp_server_addr[i]));
    	udp_server_addr[i].sin_family = AF_INET;
    	udp_server_addr[i].sin_addr.s_addr = INADDR_ANY;
    	udp_server_addr[i].sin_port = htons(UDP_PORT+i);

    	if (bind(uds[i], (struct sockaddr *)&udp_server_addr[i], sizeof(udp_server_addr[i])) < 0) 
    	{
        	perror("UDP socket bind failed");
        	exit(EXIT_FAILURE);
    	}
    }
    printf("UDP servers are waiting on port numbers 12345 and 12346\n");
    while (1) 
    {
        FD_ZERO(&rfds); // Clear the socket set
        FD_SET(uds[0], &rfds); // Add UDP socket
        FD_SET(uds[1], &rfds); // Add UDP socket
        
        maxsd = (uds[0] > uds[1]) ? uds[0] : uds[1];

        rval = select(maxsd + 1, &rfds, NULL, NULL, NULL);

        if ((rval < 0) && (errno != EINTR)) 
	{
            perror("select error");
        }

        if (FD_ISSET(uds[0], &rfds)) 
	{
            int n = recvfrom(uds[0], buf1, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&client_addr[0], &client_addr_len);
            if (n < 0) 
	    {
                perror("UDP recvfrom failed");
                exit(EXIT_FAILURE);
            }
            buf1[n] = '\0';
            printf("Received UDP message from %s:%d: %s\n", inet_ntoa(client_addr[0].sin_addr), ntohs(client_addr[0].sin_port), buf1);
	    sendto(uds[0], buf1, strlen(buf1), 0, (const struct sockaddr *)&client_addr[0], client_addr_len);

        }
	if (FD_ISSET(uds[1], &rfds))
        {
            int n = recvfrom(uds[1], buf2, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&client_addr[1], &client_addr_len);
            if (n < 0)
            {
                perror("UDP recvfrom failed");
                exit(EXIT_FAILURE);
            }
            buf2[n] = '\0';
            printf("Received UDP message from %s:%d: %s\n", inet_ntoa(client_addr[1].sin_addr), ntohs(client_addr[1].sin_port), buf2);
	    sendto(uds[1], buf2, strlen(buf2), 0, (const struct sockaddr *)&client_addr[1], client_addr_len);
        }


    }

    close(uds[0]);
    close(uds[1]);

    return 0;
}

