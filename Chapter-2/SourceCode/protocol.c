#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Packet
{
	unsigned int f1:1;
	unsigned int f2:1;
	unsigned int f3:3;
	unsigned int f4:3;
	char src;
	char dst;
	char data;

};

int main()
{
	struct Packet p1;
	printf("Size of packet:%ld\n",sizeof(p1));

	p1.f1=0;
	p1.f2=1;
	p1.f3=7;
	p1.f4=4;
	p1.src='A';
	p1.dst='D';
	p1.data='H';
	
	printf("Packet contents:\n");
	printf("%u %u %u %u %c %c %c\n",p1.f1,p1.f2,p1.f3,p1.f4,p1.src,p1.dst,p1.data);
	

	printf("Parsing Packet of 4 bytes\n");
	char buffer[4];
	memcpy(buffer,&p1,4);
	for (int i=0;i<4;i++)
	{
		if (i==0)
		{
			printf("Flag1: %u Flag2: %u Flag3:%u Flag4:%u\n", (buffer[i]&0x01), (buffer[i]&0x02) >> 1, (buffer[i]&0x1C) >> 2, (buffer[i]&0xE0) >> 5);
		}
		if (i==1)
		{
			printf("Source Address: %c \n",buffer[i]);
		}
		if (i==2)
		{
			printf("Destination Address: %c \n",buffer[i]);
		}
		if (i==3)
		{
			printf("Data: %c \n",buffer[i]);
		}
	}


	return 0;
}
