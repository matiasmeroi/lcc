#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "Barreras.h"

barrier_t barrera;

void* hiloCuerpo(void* arg) 
{
	sleep(rand() % 4 + 1);
	printf("Fin FC1 en Hilo: %d\n", *((int*) arg));

	barrier_wait(&barrera);

	printf("FC2 en Hilo: %d\n", *((int*) arg));

	pthread_exit(0);
}

int main() 
{
	printf("Inicio main\n");

	srand(time(NULL));

	int nHilos = 14;

	barrier_init(&barrera, nHilos);

	pthread_t hilos[nHilos];
	int id[nHilos];
	for(int i = 0; i < nHilos; i++) 
	{
		id[i] = i;
		pthread_create(&hilos[i], NULL, hiloCuerpo, (void*) &id[i]);
	}

	for(int i = 0; i < nHilos; i++)
		pthread_join(hilos[i], NULL);

	barrier_destroy(&barrera);

	printf("Fin main\n");
	return 0;
}
