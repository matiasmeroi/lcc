#ifndef _BARRERAS_H_
#define _BARRERAS_H_

#include <pthread.h>

/* Definición de la estructura y sinónimo de tipo. */
struct cond_barrier {
	int counter;
	int nHilos;  // cantidad de hilos a esperar
	pthread_cond_t cond;
	pthread_mutex_t mutex;
};

typedef struct cond_barrier barrier_t;

/*************/

/*************/
/* Operaciones */

/* 
 * Creación de una barrera de condición, tomando como argumento la cantidad
 * de hilos que se van a esperar 
 */
int barrier_init(barrier_t *barr, unsigned int count);

/* Función *bloqueante* para esperar a los demás hilos */
int barrier_wait(barrier_t *barr);

/* Eliminación de la barrera */
int barrier_destroy(barrier_t *barr);

#endif
