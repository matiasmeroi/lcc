#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N_FILOSOFOS 5
#define ESPERA 5000000

pthread_mutex_t tenedor[N_FILOSOFOS];

void pensar(int i)
{
  printf("Filosofo %d pensando...\n",i);
  usleep(random() % ESPERA);
}

void comer(int i)
{
  printf("Filosofo %d comiendo...\n",i);
  usleep(random() % ESPERA);
}

void tomar_tenedores(int i)
{
  pthread_mutex_lock(&tenedor[i]); /* Toma el tenedor a su derecha */
  pthread_mutex_lock(&tenedor[(i+1)%N_FILOSOFOS]); /* Toma el tenedor a su izquierda */
}

void dejar_tenedores(int i)
{
  pthread_mutex_unlock(&tenedor[i]); /* Deja el tenedor de su derecha */
  pthread_mutex_unlock(&tenedor[(i+1)%N_FILOSOFOS]); /* Deja el tenedor de su izquierda */
}

void *filosofo(void *arg)
{
  int i = *((int*)arg);
  for (;;)
  {
    tomar_tenedores(i);
    comer(i);
    dejar_tenedores(i);
    pensar(i);
  }
}

void* filosofoSurdo(void* arg) 
{
  
  int i = *((int*)arg);
  for( ; ; )
  {

    // tomar tenedores
    pthread_mutex_lock(&tenedor[(i + 1) % N_FILOSOFOS]);
    pthread_mutex_lock(&tenedor[i % N_FILOSOFOS]);

    comer(i);

    // dejar tenedores
    pthread_mutex_unlock(&tenedor[(i + 1) % N_FILOSOFOS]);
    pthread_mutex_unlock(&tenedor[i % N_FILOSOFOS]);

    pensar(i);

  }
}

int main()
{
  int id[] = {1, 2, 3, 4, 5};
  
  pthread_t filo[N_FILOSOFOS];
  for (int i=0;i<N_FILOSOFOS;i++)
    pthread_mutex_init(&tenedor[i], NULL);

  /* Se crea el filósofo zurdo en la  posición 0 */
  
  pthread_create(&filo[0], NULL, filosofoSurdo, (void*) id);

  /* El resto de los filósofos son diestros */
  for (int i=1;i<N_FILOSOFOS;i++)
    pthread_create(&filo[i], NULL, filosofo, (void *) (id + i));

  pthread_join(filo[0], NULL);
  return 0;
}

























