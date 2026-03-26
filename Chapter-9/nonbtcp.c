#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>


#include <fcntl.h>
#include <unistd.h> 

int block2nonblock(int tcp_bsd) 
{
    int flags = fcntl(tcp_bsd, F_GETFL, 0);
    if (flags == -1) 
    {
        perror("fcntl(F_GETFL)");
        return -1;
    }

    if (fcntl(tcp_bsd, F_SETFL, flags | O_NONBLOCK) == -1) 
    {
        perror("fcntl(F_SETFL)");
        return -1;
    }
    return 0;
}
int main() 
{
    int tcp_ls[2], tcp_cs[10];
    struct sockaddr_in server[2], client[2];
    socklen_t client_len;
    char buf[1024];
    fd_set rfds;
    struct timeval waitime;
    for(int i=0;i<2;i++)
    {
    	tcp_ls[i] = socket(AF_INET, SOCK_STREAM, 0);
    	if (tcp_ls[i] < 0) 
	{ 
	    perror("socket"); exit(EXIT_FAILURE); 
	}

    	if (block2nonblock(tcp_ls[i]) < 0) 
	{ 
	   close(tcp_ls[i]); exit(EXIT_FAILURE); 
	}

    	memset(&server[i], 0, sizeof(server[i]));
    	server[i].sin_family = AF_INET;
    	server[i].sin_addr.s_addr = INADDR_ANY;
    	server[i].sin_port = htons(12345+i);
    	if (bind(tcp_ls[i], (struct sockaddr *)&server[i], sizeof(server[i])) < 0) 
	{ 
	    perror("bind"); close(tcp_ls[i]); exit(EXIT_FAILURE); 
	}
    	if (listen(tcp_ls[i], 5) < 0) 
	{ 
	   perror("listen"); close(tcp_ls[i]); exit(EXIT_FAILURE); 
	}
    }
    printf("TCP Servers listening on ports 12345 and 12346 ...\n");
    for (int i=0;i<20;i++)
    {
    	tcp_cs[i] = -1;
    }	
			  
    int c=0;
    while (1) 
    {
        FD_ZERO(&rfds);
        int maxfd = tcp_ls[0]>tcp_ls[1]?tcp_ls[0]:tcp_ls[1];

        FD_SET(tcp_ls[0], &rfds);
        FD_SET(tcp_ls[1], &rfds);
	
	for (int i=0;i<10;i++)
        if (tcp_cs[i] != -1) 
	{
            FD_SET(tcp_cs[i], &rfds);
            if (tcp_cs[i] >= maxfd) maxfd = tcp_cs[i];
        }

        waitime.tv_sec = 1; // 1 second waitime for select
        waitime.tv_usec = 0;
        int rval = select(maxfd + 1, &rfds, NULL, NULL, &waitime);
        if (rval < 0 && errno != EINTR) 
	{ 
	    perror("select error"); exit(EXIT_FAILURE); 
	}
        if (rval == 0) 
	{ 
	    continue; 
	}
	for (int i=0;i<2;i++)
        if (FD_ISSET(tcp_ls[i], &rfds)) 
	{
            client_len = sizeof(client);
            tcp_cs[c] = accept(tcp_ls[i], (struct sockaddr *)&client[i], &client_len);
            if (tcp_cs[c] < 0) 
	    {
                if (errno == EAGAIN || errno == EWOULDBLOCK) 
		{
                    // No pending connections
                } 
		else 
		{
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
            } 
	    else 
	    {
		 if (block2nonblock(tcp_cs[c]) < 0) 
		 { 
		     close(tcp_cs[c]); tcp_cs[c] = -1; continue; 
		 }
                 printf("New connection accepted from %s:%d\n", inet_ntoa(client[i].sin_addr), ntohs(client[i].sin_port));
		 c++;
            }

        }

	for (int i=0;i<10;i++)
        if (tcp_cs[i] != -1 && FD_ISSET(tcp_cs[i], &rfds)) 
	{
            ssize_t rcnt = read(tcp_cs[i], buf, sizeof(buf) - 1);
            if (rcnt < 0) 
	    {
                if (errno == EAGAIN || errno == EWOULDBLOCK) 
		{
                    // No data available to read yet
                } 
		else 
		{
                    perror("read");
                    close(tcp_cs[i]);
                    tcp_cs[i] = -1;
                }
            } 
	    else if (rcnt == 0) 
	    {
                printf("Client disconnected.\n");
                close(tcp_cs[i]);
                tcp_cs[i] = -1;
            } 
	    else 
	    {
                buf[rcnt] = '\0';
                printf("Received from client: %s\n", buf);
                ssize_t wcnt = write(tcp_cs[i], buf, rcnt);
            }
        }
    }
    close(tcp_ls[0]);
    close(tcp_ls[1]);
    return 0;
}
