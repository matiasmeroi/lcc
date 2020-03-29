#ifndef _SEMAFORO_H_
#define _SEMAFORO_H_

#include <pthread.h>

struct semaphore_t {
	pthread_mutex_t mut;
	int value;
};

typedef struct semaphore_t sem_t;

/* Funcion de creación de Semáforo */
int sem_init(sem_t * sem, int init);

/* Incremento del Semáforo */
int sem_incr(sem_t * sem);

/* Decremento del semáforo. Notar que es una funciçon que puede llegar
	 a bloquear el proceso */
int sem_decr(sem_t * sem);

/* Destrucción de un semáforo */
int sem_destroy(sem_t * sem);

#endif
