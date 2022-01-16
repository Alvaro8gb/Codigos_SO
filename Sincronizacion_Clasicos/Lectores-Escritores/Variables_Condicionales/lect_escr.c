#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_TOTAL_LECTORES 6
#define NUM_TOTAL_ESCRITORES 2


int dato = 0;       /* recurso */
int n_lectores = 0; /* numero de lectores */
pthread_mutex_t mux ; // sem_t sem_lec;      /* controlar el acceso n_lectores */
sem_t cerrojo;      /* controlar el acceso a dato */ /* solo un escritor modificando el recurso*/

void * Lector(void * arg) {
  
  for (int i = rand()%10;i>0;i--) {

    int id = (int) arg;

    pthread_mutex_lock(&mux) ; // sem_wait(&sem_lec);

    n_lectores = n_lectores + 1;

    if (n_lectores == 1)
      sem_wait(&cerrojo);

    pthread_mutex_unlock(&mux) ; // sem_post(&sem_lec);

    /* leer dato */
    printf("El lector\t%d lee dato:\t%d\n",id, dato); //  pthread_self()
    
    pthread_mutex_lock(&mux) ; // sem_wait(&sem_lec);

    n_lectores = n_lectores - 1;

    if (n_lectores == 0)
      sem_post(&cerrojo);

    pthread_mutex_unlock(&mux) ; // sem_post(&sem_lec);
    
    sleep(rand()%10);
  }

  pthread_exit(0);
}

void * Escritor(void * arg) {
  
  int id = (int) (arg);
  for (int i = rand()%10;i>0;i--) {
    sem_wait(&cerrojo);

    /* modificar el recurso */
    dato = dato + 2;
    printf("El escritor\t%d modifica dato:\t%d\n", id, dato); // pthread_self()

    sem_post(&cerrojo);

    sleep(rand()%20);
  }
  pthread_exit(0);
}

int main(void) {
  pthread_t lectores[NUM_TOTAL_LECTORES], escritores[NUM_TOTAL_ESCRITORES];

  printf("Iniciamos lectores/escritores con dato:\t\t%d\n", dato);
  
  sem_init(&cerrojo, 0, 1);   
  pthread_mutex_init(&mux,NULL); //sem_init(&sem_lec, 0, 1);

  for(int i = 0 ; i < NUM_TOTAL_LECTORES ; i++)
        pthread_create(&lectores[i], NULL, Lector, (void *) i);

  for(int i = 0 ; i < NUM_TOTAL_ESCRITORES ; i++)
        pthread_create(&escritores[i], NULL, Escritor,(void *) i);


  for(int i = 0 ; i < NUM_TOTAL_LECTORES ; i++)
        pthread_join(lectores[i],NULL);

  for(int i = 0 ; i < NUM_TOTAL_ESCRITORES ; i++)
        pthread_join(escritores[i],NULL);


  sem_destroy(&cerrojo);    
  pthread_mutex_destroy(&mux); // sem_destroy(&sem_lec);

  printf("Proceso finalizado, dato:\t%d\n", dato);
  exit(0);
}
