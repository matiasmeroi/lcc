#include "semaforo.h"
#include <stdio.h>
#include <unistd.h>

sem_t semaforo;

void* prod(void* arg) 
{
	sleep(2);
	sem_incr(&semaforo);
	printf("%s\n", "P");
}

void* cons(void* arg) 
{	
	sem_decr(&semaforo);
	printf("%s\n", "C");
	return NULL;
}

int main() 
{
	sem_init(&semaforo, 0);

	pthread_t t1, t2;
	pthread_create(&t1, NULL, prod, NULL);
  pthread_create(&t2, NULL, cons, NULL);

  pthread_join(t2, NULL);

	sem_destroy(&semaforo);
	return 0;
}
