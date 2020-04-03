#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define N_THREADS 	20
#define N_CUENTAS   10

pthread_mutex_t locks[N_THREADS];
int cuentas[N_CUENTAS];

/*
 * Puede producir deadlock
 */
int transferir(int cuenta_fuente, int cuenta_destino, int cantidad)
{
	int rta;
	pthread_mutex_lock(&locks[cuenta_fuente]);
	pthread_mutex_lock(&locks[cuenta_destino]);
	if (cuentas[cuenta_fuente] >= cantidad) 
	{
		rta = 0;
		cuentas[cuenta_fuente] -= cantidad;
		cuentas[cuenta_destino] += cantidad;
	}
	else
		rta = 1;
	pthread_mutex_unlock(&locks[cuenta_destino]);
	pthread_mutex_unlock(&locks[cuenta_fuente]);
	return rta;
}

/*
 * Si despues de conseguir el primer lock no puede conseguir el segundo, libera
 * el primer lock y despues de 1 ms intenta nuevamente
 */
int transferir_trylock(int cuenta_fuente, int cuenta_destino, int cantidad)
{
	int rta;

	int boo = 1;
	while(boo)
	{
		pthread_mutex_lock(&locks[cuenta_fuente]);
		
		/* Intenta obtener el lock para la cuenta destino */
		if(pthread_mutex_trylock(&locks[cuenta_destino]) != 0) 
		{
			printf("No se consiguio %d\n", cuenta_destino);
			pthread_mutex_unlock(&locks[cuenta_fuente]);
			usleep(1000);
		}
		else
		{
			boo = 0;
		}
	}

	if (cuentas[cuenta_fuente] >= cantidad) 
	{
		rta = 0;
		cuentas[cuenta_fuente] -= cantidad;
		cuentas[cuenta_destino] += cantidad;
	}
	else
		rta = 1;

	pthread_mutex_unlock(&locks[cuenta_destino]);
	pthread_mutex_unlock(&locks[cuenta_fuente]);

	return rta;
}

/*
 * Intenta conseguir los locks en el orden en el que estan almacenados en el arreglo
 */
int transferir_minimo(int cuenta_fuente, int cuenta_destino, int cantidad)
{
	int rta = 0;

	pthread_mutex_lock(&locks[cuenta_fuente < cuenta_destino ? cuenta_fuente : cuenta_destino]);
	pthread_mutex_lock(&locks[cuenta_fuente < cuenta_destino ? cuenta_destino : cuenta_fuente]);

	if(cuentas[cuenta_fuente] >= cantidad)
	{
		cuentas[cuenta_destino] += cantidad;
		cuentas[cuenta_fuente] -= cantidad;
		rta = 0;
	}
	else
		rta = 1;

	pthread_mutex_unlock(&locks[cuenta_fuente]);
	pthread_mutex_unlock(&locks[cuenta_destino]);
	return rta;
}

void* hilo(void* arg)
{
	int fuente = rand() % N_CUENTAS;

	int destino = fuente;
	while(destino == fuente) destino = rand() % N_CUENTAS;

	int cantidad = rand() % 1000;
	
	printf("Transferir de %d a %d\n", fuente, destino);
	transferir_minimo(fuente, destino, cantidad);
}

int main() 
{
	srand(time(NULL));

	for(int i = 0; i < N_CUENTAS; i++)
	{
		cuentas[i] = rand() % 1000;
		pthread_mutex_init(&locks[i], NULL);
	}

	pthread_t hilos[N_THREADS];
	for(int i = 0; i < N_THREADS; i++)
		pthread_create(&hilos[i], NULL, hilo, NULL);

	for(int i = 0; i < N_THREADS; i++)
		pthread_join(hilos[i], NULL);

	printf("Fin\n");

	return 0;
}


