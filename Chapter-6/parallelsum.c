#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#define ARRAY_SIZE 50000
#define NofT 200

pthread_mutex_t mutex;
typedef struct 
{
	int tid;
    	int* list;
    	int start;
    	int end;
} FunArgs;

int result=0;
void* ParallelSum(void* arg) 
{
    	FunArgs* data = (FunArgs*)arg;
    	for (int i = data->start; i < data->end; i++) 
    	{
    		pthread_mutex_lock(&mutex);
        	result = result+data->list[i];
    		pthread_mutex_unlock(&mutex);
    	}

	printf("Total: %d\n",result);
}

int main() 
{
	int* list = (int*)malloc(ARRAY_SIZE * sizeof(int));
	for (int i = 0; i < ARRAY_SIZE; i++) 
	{
		list[i]=i;
	}
	pthread_t threads[NofT];
    	pthread_mutex_init(&mutex, NULL);
	FunArgs args[NofT];
	int npt = ARRAY_SIZE / NofT;
	printf("NoElePerThread %d\n",npt);
	int remels = ARRAY_SIZE % NofT;
	int start = 0;

	double time1, timedif;
        time1 = (double) clock();
        time1 = time1 / CLOCKS_PER_SEC;


	for (int i = 0; i < NofT; i++) 
	{
	    	args[i].tid = i;
	    	args[i].list = list;
	    	args[i].start = start;
	    	args[i].end = start + npt;
	    	if (i == NofT - 1) 
	    	{
	      		args[i].end += remels;
	    	}
	    	pthread_create(&threads[i], NULL, ParallelSum, &args[i]);
	    	start = args[i].end;
	}
	for (int i = 0; i < NofT; i++) 
	{
	    	pthread_join(threads[i], NULL);
	}
	unsigned int total=0;
	printf("Total: %d",result);
	timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
        printf("Mutex time is %lf seconds\n", timedif);

	free(list);

	pthread_mutex_destroy(&mutex);
	return 0;
}
