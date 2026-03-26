#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>
typedef struct 
{
	int* list;
    	int start;
    	int end;
    	int ele;
    	int result;
} FunArgs1;


typedef struct 
{
    	int* list;
    	int start;
    	int end;
    	int min;
} FunArgs2;

typedef struct 
{
    	int* list;
    	int start;
    	int end;
    	int ele;
    	float mean;
} FunArgs3;

void* Search(void* arg) 
{
    	FunArgs1* data = (FunArgs1*)arg;
    	for (int i = data->start; i < data->end; i++) 
	{
        	if (data->list[i] == data->ele) 
		{
            		data->result=1;
	    		break;
        	}
    	}
}

void* MinElement(void* arg) 
{
    	FunArgs2* data = (FunArgs2*)arg;
   	int min=data->list[data->start];
    	for (int i = data->start; i < data->end; i++) 
    	{
        	if (data->list[i] <= min) 
		{
           		min = data->list[i]; 
        	}
    	}
    	data->min = min;
}


void* Mean(void* arg) 
{
    	FunArgs3* data = (FunArgs3*)arg;
    	float sum=0.0;
    	for (int i = data->start; i < data->end; i++) 
	{
	    sum = sum+data->list[i];
        }
    	data->mean = (float)(sum)/(data->end-data->start);
}



int main() 
{
    	int n, s, nthrds;
    	printf("Enter the number of elements in the listay: ");
    	scanf("%d", &n);

    	int* list = (int*)malloc(n * sizeof(int));
    	printf("Enter the elements of the listay:\n");
    	for (int i = 0; i < n; i++) 
    	{
    		scanf("%d", &list[i]);
    	}
    	printf("Enter the search element ");
    	scanf("%d", &s);
    	pthread_t threads[3];
    	FunArgs1 args1;
    	args1.list = list;
    	args1.start = 0;
    	args1.end = n-1;
    	args1.ele = s;
    	pthread_create(&threads[0], NULL, Search, &args1);


    	FunArgs2 args2;
    	args2.list = list;
    	args2.start = 0;
    	args2.end = n-1;
    	pthread_create(&threads[1], NULL, MinElement, &args2);


    	FunArgs3 args3;
    	args3.list = list;
    	args3.start = 0;
    	args3.end = n-1;
    	pthread_create(&threads[2], NULL, Mean, &args3);


    	for (int i = 0; i <3; i++) 
	{
        	pthread_join(threads[i], NULL);
   	}

    	printf("Search Result %d\n", args1.result);
    	printf("Minimum Element %d\n", args2.min);
    	printf("Mean %f\n", args3.mean);
    	free(list);
    	return 0;
}
