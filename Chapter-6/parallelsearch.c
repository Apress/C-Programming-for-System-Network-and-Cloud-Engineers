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
    	int key;
    	int result;
} FunArgs;

void* ParallelSearch(void* arg) 
{
    	FunArgs* data = (FunArgs*)arg;
    	for (int i = data->start; i < data->end; i++) 
    	{
        	if (data->list[i] == data->key) 
		{
            		data->result=1;
	    		break;
        	}
    	}
}

int main() 
{
	int n, s, nthrds;
	printf("Enter the number of keyments in the listay: ");
	scanf("%d", &n);
	
	int* list = (int*)malloc(n * sizeof(int));
	printf("Enter the keyments of the listay:\n");
	for (int i = 0; i < n; i++) 
	{
		scanf("%d", &list[i]);
	}

	printf("Enter the search element: ");
	scanf("%d", &s);
	printf("Enter the number of threads: ");
	scanf("%d", &nthrds);
	pthread_t threads[nthrds];
	FunArgs args[nthrds];
	int npt = n / nthrds;
	int remels = n % nthrds;
	int start = 0;
	for (int i = 0; i < nthrds; i++) 
	{
	    	args[i].list = list;
	    	args[i].start = start;
	    	args[i].end = start + npt;
	    	args[i].key = s;
	    	if (i == nthrds - 1) 
	    	{
	      		args[i].end += remels;
	    	}
	    	pthread_create(&threads[i], NULL, ParallelSearch, &args[i]);
	    	start = args[i].end;
	}
	for (int i = 0; i < nthrds; i++) 
	{
	    	pthread_join(threads[i], NULL);
	}
	for (int i = 0; i < nthrds; i++) 
	{
	    	if (args[i].result == 1) 
	    	{
	      		printf("Element found");
	     	 	break;
	    	}
	}

	free(list);
	return 0;
}
