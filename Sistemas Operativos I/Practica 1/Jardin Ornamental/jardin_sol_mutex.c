
#define N 100000

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void* hilo(void* arg) {
	for(int i = 0; i < N; i++) {

		pthread_mutex_lock(&mut);
		(*(int*) arg)++;
		pthread_mutex_unlock(&mut);

	}
	return NULL;
}

int main() {
	pthread_t t1, t2;

	int *counter = malloc(sizeof(int));
  *counter = 0;

	pthread_create(&t1, NULL, hilo, counter);
	pthread_create(&t2, NULL, hilo, counter);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Visitantes: %d\n", *counter);

	free(counter);

	return 0;
}
