#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t crits1;

void *critSecAccess(void *arg) 
{
    	for (int i = 0; i < 100000; i++) 
    	{
        	counter++;
    	}
    	return NULL;
}


int main() 
{
    	pthread_t tr1, tr2;
	pthread_mutex_init(&crits1, NULL);
	
	pthread_create(&tr1, NULL, critSecAccess, NULL);
	pthread_create(&tr2, NULL, critSecAccess, NULL);
	
	pthread_join(tr1, NULL);
	pthread_join(tr2, NULL);
	
	printf("Counter value: %d\n", counter);
	
	pthread_mutex_destroy(&crits1);
	return 0;
}
