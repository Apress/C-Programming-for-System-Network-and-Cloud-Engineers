#include<stdio.h>
#define DONE 1
#define NONE 0
int left(int steps, char *action)
{
	for(int i=0;i<steps;i++)
	{
		printf("L <-- ");
	}
	printf("\n");
	if (action!=NULL)
	{	
		printf("%s\n",action);
		return DONE;
	}
	else
	{
		return NONE;
	}
}

int right(int steps, char *action)
{
	for(int i=0;i<steps;i++)
	{
		printf("R --> ");
	}
	printf("\n");
	if (action!=NULL)
	{	
		printf("%s\n",action);
		return DONE;
	}
	else
	{
		return NONE;
	}
}

int up(int steps, char *action)
{
	for(int i=0;i<steps;i++)
	{
		printf("U ^");
	}
	printf("\n");
	if (action!=NULL)
	{	
		printf("%s\n",action);
		return DONE;
	}
	else
	{
		return NONE;
	}
}

int down(int steps, char *action)
{
	for(int i=0;i<steps;i++)
	{
		printf("D .");
	}
	printf("\n");
	if (action!=NULL)
	{	
		printf("%s\n",action);
		return DONE;
	}
	else
	{
		return NONE;
	}
}
int main()
{
	printf("Robo 1:\n");
	unsigned int status;
	
	left(5,"Trees planting");
	right(3,"Watering");
	up(4,"Serving Food");

	status = down(5,"Charging and Rest");
	if (status==1)
	{
		printf("Robo 1 Successfully at rest place\n");
	}

	printf("Robo 2:\n");
	up(4,"Serving Food");
	right(3,"Watering");
	left(5,"Trees planting");
	down(2,"Charging and Rest");
	printf("Tasks over!\n");

}
