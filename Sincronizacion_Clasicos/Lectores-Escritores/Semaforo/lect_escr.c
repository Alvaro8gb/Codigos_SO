#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_TOTAL_LECTORES 6
#define NUM_TOTAL_ESCRITORES 2


int dato = 0;       /* recurso */
int n_lectores = 0; /* numero de lectores */
int n_escritores = 0; /* numero de lectores */
int  wr_in_sc = 0; 

pthread_mutex_t mux ; // sem_t sem_lec;      /* controlar el acceso n_lectores */
sem_t cerrojo;      /* controlar el acceso a dato */ /* solo un escritor modificando el recurso*/
pthread_cond_t avisar_escritores;
pthread_cond_t avisar_lectores;

void * Lector(void * arg) {
  
  for (int i = rand()%10;i>0;i--) {

    int id = (int) arg;

    
    pthread_mutex_lock(&mux) ;

    while(n_escritores > 0){
      pthread_cond_wait(&avisar_escritores, &mux);
    }

    n_lectores++;
    
    pthread_mutex_unlock(&mux) ;


    /* leer dato */
    printf("El lector\t%d lee dato:\t%d\n",id, dato); //  pthread_self()
    
    pthread_mutex_lock(&mux) ;

    n_lectores--;

    if(n_lectores == 0){
      pthread_cond_signal(&avisar_escritores);
    }

    pthread_mutex_unlock(&mux) ;
    
    sleep(4);
  }

  pthread_exit(0);
}

void * Escritor(void * arg) {
  
  int id = (int) (arg);
  for (int i = rand()%10;i>0;i--) {

    pthread_mutex_lock(&mux) ;
    n_escritores++;


    while(n_lectores > 0 && wr_in_sc){
        pthread_cond_wait(&avisar_escritores,&mux);
    }

     wr_in_sc=1;

    pthread_mutex_unlock(&mux) ;

    /* modificar el recurso */
    dato = dato + 2;
    printf("El escritor\t%d modifica dato:\t%d\n", id, dato); // pthread_self()

    
    pthread_mutex_lock(&mux) ;
    n_escritores--;
    wr_in_sc=0;


    if(n_escritores > 0 ){ // preferencia a los escritores
      pthread_cond_signal(&avisar_escritores);
    }
    else{
      pthread_cond_signal(&avisar_lectores);
    }
    pthread_mutex_lock(&mux) ;

    sleep(4);
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
