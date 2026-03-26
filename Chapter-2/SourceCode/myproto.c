#include<stdio.h>
#include<string.h>

struct L1
{
        char src[9];
        char dst[9];
};
struct L2
{
        unsigned int src;
        unsigned int dst;

};
struct L3
{
        char src[5];
        char dst[5];
};

struct MyProto
{
	int type;
	union PacketAddress
	{
		struct L1 l1;
		struct L2 l2;
		struct L3 l3;

	};
        union PacketAddress address; 
	char buffer[100];


};
struct MyProto Packet(int t, char *pkt)
{
	struct MyProto p1;
	if (t == 1)
	{
		p1.type = t;
		strcpy(p1.address.l1.src,"aabbccdd");
		p1.address.l1.src[8]='\0';
		strcpy(p1.address.l1.dst,"aabbccde");
		p1.address.l1.dst[8]='\0';
	}
	if (t == 2)
	{
		p1.type = t;
		p1.address.l2.src=12345;
		p1.address.l2.dst=54321;
	}
	if (t == 3)
	{
		p1.type = t;
		strcpy(p1.address.l3.src,"aabb");
		p1.address.l3.src[4]='\0';
		strcpy(p1.address.l3.dst,"aadd");
		p1.address.l3.dst[4]='\0';
	}
	if (pkt!=NULL)
	{
		strcpy(p1.buffer,pkt);
	}
	return p1;
		
}

void PacketDisplay(struct MyProto *p1)
{
	printf("Type: %d", p1->type);
	if (p1->type == 1)
	{
		printf("Src: %s", p1->address.l1.src);
		printf("Dst: %s", p1->address.l1.dst);
	}
	if (p1->type == 3)
	{
		printf("Src: %s", p1->address.l3.src);
		printf("Dst: %s", p1->address.l3.dst);
	}
	if (p1->type == 2)
	{

		printf("Src: %u", p1->address.l2.src);
		printf("Dst: %u", p1->address.l2.dst);
	}
	printf("Data: %s\n", p1->buffer);


}
int main()
{
	struct MyProto p1,p2,p3;
	p1 = Packet(1,"hello");
	p2 = Packet(2,"hello");
	p3 = Packet(3,"hello");
	PacketDisplay(&p1);
	PacketDisplay(&p2);
	PacketDisplay(&p3);
	return 0;
}
