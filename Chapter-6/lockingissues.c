#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t crits1;
pthread_mutex_t crits2;

void *critSecAccess1(void *arg) 
{
    	pthread_mutex_lock(&crits1);
    	pthread_mutex_lock(&crits2);
    	for (int i = 0; i < 100000; i++) 
    	{
        	counter++;
    	}
    	pthread_mutex_unlock(&crits2);
    	pthread_mutex_unlock(&crits1);
    	return NULL;
}

void *critSecAccess2(void *arg) 
{
    	pthread_mutex_lock(&crits2);
    	pthread_mutex_lock(&crits1);
    	for (int i = 0; i < 100000; i++) 
	{
        	counter++;
    	}
    	pthread_mutex_unlock(&crits1);
    	pthread_mutex_unlock(&crits2);
    	return NULL;
}

int main() 
{
    	pthread_t tr1, tr2;
	pthread_mutex_init(&crits1, NULL);
	pthread_mutex_init(&crits2, NULL);
	
	pthread_create(&tr1, NULL, critSecAccess1, NULL);
	pthread_create(&tr2, NULL, critSecAccess2, NULL);
	
	pthread_join(tr1, NULL);
	pthread_join(tr2, NULL);
	
	printf("Counter value: %d\n", counter);
	
	pthread_mutex_destroy(&crits1);
	pthread_mutex_destroy(&crits2);
	return 0;
}
