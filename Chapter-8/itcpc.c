#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <errno.h>
#define PORT_NUMBER 12346 
#define SERVER_IP_ADDRESS "127.0.0.1"
#define BUF_SIZE 10

int main()
{
    	int tcp_cs;
    	struct sockaddr_in server_address;

    	FILE *fptr;
    	char buf[BUF_SIZE];
    	char buf2[10];
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
            exit(EXIT_FAILURE);
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

    	while (fread(buf,1, BUF_SIZE, fptr)>0)
    	{
            if (send(tcp_cs, buf, strlen(buf), 0) == -1)
            {
		perror("Error sending data");
		break;
            }
 	    printf("Sent: %s\n", buf);
	    ssize_t rcnt = recv(tcp_cs, buf2, sizeof(buf2), 0);
            if (rcnt == -1)
            {
            	perror("Error receiving data");
                exit(EXIT_FAILURE);
	    }
            if (rcnt == 0)
            {
            	perror("closing connection");
                exit(EXIT_FAILURE);
            }
	    buf2[rcnt] = '\0';
            printf("Received: %s %d\n", buf2,rcnt);
    	}
    	fclose(fptr);
	printf("End of the file");
    	close(tcp_cs);

	return 0;
}

