#include<stdio.h>
#define DONE 1
#define NONE 0
int move(char direction, int steps, char *action)
{
	for(int i=0;i<steps;i++)
	{
		if (direction=='L')
			printf("L <-- ");
		else if (direction=='R')
			printf("R -->");
		else if (direction=='U')
			printf("U ^");
		else if (direction=='D')
			printf("D . ");
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
	
	move('L',5,"Trees planting");
	move('R',3,"Watering");
	move('U',4,"Serving Food");

	status = move('D',5,"Charging and Rest");
	if (status==1)
	{
		printf("Robo 1 Successfully at rest place\n");
	}

	printf("Robo 2:\n");
	move('U',4,"Serving Food");
	move('D',3,"Watering");
	move('L',5,"Trees planting");
	move('R',2,"Charging and Rest");
	printf("Tasks over!\n");

}
