#include "semaforo.h"
#include <stdlib.h>

#include <stdio.h>


int sem_init(sem_t* sem, int init) {
	sem->value = init;
	return pthread_mutex_init(&sem->mut, NULL);
}

int sem_incr(sem_t* sem) {
	pthread_mutex_lock(&sem->mut);
	sem->value++;
	pthread_mutex_unlock(&sem->mut);
	return 0;
}

int sem_decr(sem_t* sem) {
	int bloquear = 1;
	while(bloquear) 
	{
		pthread_mutex_lock(&sem->mut);
		bloquear = sem->value == 0;
		pthread_mutex_unlock(&sem->mut);
	}

	pthread_mutex_lock(&sem->mut);
	sem->value--;
	pthread_mutex_unlock(&sem->mut);
}

int sem_destroy(sem_t* sem) {
	return pthread_mutex_destroy(&sem->mut);
}


