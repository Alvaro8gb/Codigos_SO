#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int a, b;
sem_t cerrojo_a, cerrojo_b;

void * thread1(void * arg) {
    printf("Thead1 ha empezado \n");

    while(1){

        sem_wait(&cerrojo_a);
        sem_wait(&cerrojo_b);

        a =1;
        b=1;

        sched_yield();
        printf("1->> a : %d y b: %d \n",a,b);

        sem_post(&cerrojo_a);
        sem_post(&cerrojo_b);
        sleep(4);
        
    }  

}
void * thread2(void * arg) {
      printf("Thead2 ha empezado \n");

    while(1){
        sem_wait(&cerrojo_a);
        sem_wait(&cerrojo_b);

        a =2;
        b=2;
        sched_yield();
        printf("2 ->> a : %d y b: %d \n",a,b);

        sem_post(&cerrojo_a);
        sem_post(&cerrojo_b);

        sleep(3);

    }
    
  

}

void * thread3(void * arg) {
    printf("Thead3 ha empezado \n");
    while(1){
        
        sem_wait(&cerrojo_a);
        a=3;
        sched_yield();
        printf("3->> a : %d \n",a);
        sem_post(&cerrojo_a);

        sleep(2);

    }
        
}
void * thread4(void * arg) {
    printf("Thead4 ha empezado \n");

    while(1){
        sem_wait(&cerrojo_b);
        b=4;
        sched_yield();
        printf("4->> b:%d \n ",b);
        sem_post(&cerrojo_b);

        sleep(2);
        
    }

}

int main() {
  pthread_t th1, th2, th3, th4;
  a = 0;
  b = 0;

  sem_init(&cerrojo_a, 0, 1);   
  sem_init(&cerrojo_b, 0, 1);   

  printf("Create the threads\n");
  printf("a :%d y b:%d \n",a,b);

  pthread_create(&th1, NULL, thread1, NULL);
  pthread_create(&th2, NULL, thread2, NULL);
  pthread_create(&th3, NULL, thread3, NULL);
  pthread_create(&th4, NULL, thread4, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);
  pthread_join(th4, NULL);

  sem_destroy(&cerrojo_a); 
  sem_destroy(&cerrojo_b); 

  return 0;
}
