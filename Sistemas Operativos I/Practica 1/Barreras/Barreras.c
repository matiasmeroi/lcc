
#include "Barreras.h"

int barrier_init(barrier_t *barr, unsigned int count) 
{
	barr->nHilos = count;
	barr->counter = 0;
	pthread_cond_init(&barr->cond, NULL);
	pthread_mutex_init(&barr->mutex, NULL);
	return 0;
}

int barrier_wait(barrier_t *barr) 
{
	pthread_mutex_lock(&barr->mutex);
	barr->counter++;
	if(barr->counter == barr->nHilos)
	{
		pthread_cond_broadcast(&barr->cond);
	}
	else
	{
		while(barr->counter < barr->nHilos)
			pthread_cond_wait(&barr->cond, &barr->mutex);
	}
	pthread_mutex_unlock(&barr->mutex);
	return 0;
}

int barrier_destroy(barrier_t *barr) 
{
	pthread_mutex_destroy(&barr->mutex);
	pthread_cond_destroy(&barr->cond);
	return 0;
}
