
#define N 100000

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int turno = 1;
int flag1 = 0, flag2 = 0;

void* hilo1(void* arg) {
	int i = 0;
	while(i < N) 
	{

		while(turno == 2) ;
			(*(int*) arg)++;
			i++;

		flag1 = 0;
		turno = 2;
	}
	return NULL;
}

void* hilo2(void* arg) {
	int i = 0;
	while(i < N)
	{

		while(turno == 1) ;
			(*(int*) arg)++;
			i++;

		flag2 = 0;
		turno = 1;
	}
	return NULL;
}

int main() {
	pthread_t t1, t2;

	int *counter = malloc(sizeof(int));
  *counter = 0;

	pthread_create(&t1, NULL, hilo1, counter);
	pthread_create(&t2, NULL, hilo2, counter);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Visitantes: %d\n", *counter);

	free(counter);

	return 0;
}
