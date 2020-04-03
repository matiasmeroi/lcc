/* Se incluyen las librerías necesarias*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

/* Estructura para los argumentos */
struct _argument {
  sem_t tabaco_papel;
  sem_t papel_fosforos;
  sem_t fosforos_tabaco;
  sem_t otra_vez;
};

typedef struct _argument args_t;

void agente(void * _args)
{
  args_t *args = (args_t *) _args;
  for (;;) {
    int caso = random() % 3;
    sem_wait(&args->otra_vez);
    switch (caso) {
      case 0:
          sem_post(&args->tabaco_papel);
          break;
      case 1:
          sem_post(&args->papel_fosforos);
          break;
      case 2:
          sem_post(&args->fosforos_tabaco);
          break;
    }
  }
  /* Dead code */
  return;
}

void fumar(int fumador)
{
    printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
    sleep(1);
}

void *fumador1(void *_arg)
{
  args_t *args = (args_t *) _arg;
  printf("Fumador 1: Hola!\n");
  for (;;) {
    sem_wait(&args->tabaco_papel);
    fumar(1);
    sem_post(&args->otra_vez);
  }
  /* Dead code*/
  pthread_exit(0);
}

void *fumador2(void *_arg)
{
  args_t *args = (args_t *) _arg;
  printf("Fumador 2: Hola!\n");
  for (;;) {
    sem_wait(&args->papel_fosforos);
    fumar(2);
    sem_post(&args->otra_vez);
  }
  /* Dead code*/
  pthread_exit(0);
}

void *fumador3(void *_arg)
{
  args_t *args = (args_t *) _arg;
  printf("Fumador 3: Hola!\n");
  for (;;) {
    sem_wait(&args->fosforos_tabaco);
    fumar(3);
    sem_post(&args->otra_vez);
  }
  /* Dead code*/
  pthread_exit(0);
}

int main()
{
  srand(time(NULL));
  /* Memoria para los hilos */
  pthread_t s1, s2, s3;
  /* Memoria dinámica para los argumentos */
  args_t *args = malloc(sizeof(args_t));

  /* Se inicializan los semáforos */
  sem_init(&args->tabaco_papel, 0, 0);
  sem_init(&args->fosforos_tabaco, 0, 0);
  sem_init(&args->papel_fosforos, 0, 0);
  sem_init(&args->otra_vez, 0, 1);
  /************/

  /* Se inicializan los hilos*/
  pthread_create(&s1, NULL, fumador1, (void*)args);
  pthread_create(&s2, NULL, fumador2, (void*)args);
  pthread_create(&s3, NULL, fumador3, (void*)args);
  /************/

  /* Y el agente que provee con los elemetos*/
  agente((void *)args);
  /************/

  return 0;
}
