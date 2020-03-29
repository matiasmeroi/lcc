#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>

#define NPoints 	10000000
#define NHilos 		2

void* calcular(void* arg) {
	long int puntosEnCirc = 0;

	for(int i = 0; i < NPoints / NHilos; i++)
	{
		double x = (double)rand() / (double) RAND_MAX;
		double y = (double)rand() / (double) RAND_MAX;

		if(x*x + y*y <= 1.0f) puntosEnCirc++;
	}

	(*((long int*)arg)) = puntosEnCirc;

	return NULL;
}

int main(void) {
	srandom(4);

	// printf("Puntos: %d, Hilos: %d\n", NPoints, NHilos);

	pthread_t threads[NHilos];

	/* Contiene la cantidad de puntos generados dentro de la circunferencia por cada pthread */
  long int nPuntos[NHilos];

	for(int i = 0; i < NHilos; i++){
		nPuntos[i] = 0;
		pthread_create(&threads[i], NULL, calcular, &nPuntos[i]);
	}

  long	int puntosEnCirc = 0;
	for(int i = 0; i < NHilos; i++)
	{
		pthread_join(threads[i], NULL);
	}

	/* Se suman todos los puntos */
	for(int i = 0; i < NHilos; i++)
	{
		// printf("NPuntos %d: %ld\n", i, nPuntos[i]);
		puntosEnCirc += nPuntos[i];
	}

	double pi = (4 * puntosEnCirc) / (double) NPoints; 

	printf("Approximación de pi con %d puntos es: %'.10f\n",NPoints,pi);

	return 0;
}
