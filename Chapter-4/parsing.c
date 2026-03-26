#include<stdio.h>
#include<string.h>
typedef struct Layer1
{
        char src[3];
        char dst[3];

}L1;
typedef struct Layer2
{
        char src[5];
        char dst[5];
}L2;
typedef struct Layer3
{
	char src[7];
	char dst[7];

}L3;

struct Application
{
	int Type;
	L1 h1;
	L2 h2;
	L3 h3;
	char message[17];
};

void parseL1(struct Application *a)
{
	printf("Parsing Layer1\n");
	char buffer[sizeof(struct Application)];
	memcpy(buffer,a,sizeof(struct Application));
	L1 *ptr=(L1*)(buffer+sizeof(int));
	printf("L1 src:%s ",ptr->src);
	printf("\n");
	printf("L1 dst:%s ",ptr->dst);
}

void parseL2(struct Application *a)
{
	printf("Parsing Layer2\n");
        char buffer[sizeof(struct Application)];
	memcpy(buffer,a,sizeof(struct Application));
        L2 *ptr=(L2*)(buffer+ sizeof(L1)+sizeof(int));
        printf("L2 src:%s ",ptr->src);
        printf("\n");
        printf("L2 dst:%s ",ptr->dst);
}
void parseL3(struct Application *a)
{
	printf("Parsing Layer3\n");
        char buffer[sizeof(struct Application)];
	memcpy(buffer,a,sizeof(struct Application));
        L3 *ptr=(L3*)(buffer+ sizeof(L1)+ sizeof(L2)+sizeof(int));
        printf("L3 src:%s ",ptr->src);
        printf("\n");
        printf("L3 dst:%s ",ptr->dst);

}

int main()
{
	struct Application a1;
	a1.Type=1;
	strcpy(a1.h1.src,"aa");
	strcpy(a1.h1.dst,"bb");

	a1.Type=2;
	strcpy(a1.h2.src,"1234");
	strcpy(a1.h2.dst,"5678");

	a1.Type=3;
	strcpy(a1.h3.src,"0x1234");
	strcpy(a1.h3.dst,"0x9090");

	strcpy(a1.message,"abcdefghabcdefgh");
	parseL1(&a1);
	printf("\n");
	parseL2(&a1);
	printf("\n");
	parseL3(&a1);
	printf("\n");
	printf("Application Message: %s",a1.message);


}
