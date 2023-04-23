#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4

sem_t semaphore;

void* mythread(void* arg){

  int* index;

  index = (int*) arg;

  printf("Thread %d Waiting for semaphore\n", *index);
  int rc = sem_wait(&semaphore);

  if(*index > 0 && rc > 0) {
    printf("cannot wait for semaphore");
    exit(EXIT_FAILURE);
  }


  printf("Thread %d obtained semaphore\n", *index);
  sleep(5);

  sem_post(&semaphore);
  printf("Thread %d released semaphore\n", *index);

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

  pthread_t thread[NUM_THREADS];
  int rc;

  sem_init(&semaphore, 0, 0);

  for (int i = 0; i<NUM_THREADS; i++) {
    int *arg = malloc(sizeof(*arg));
        if ( arg == NULL ) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }

        *arg = i;
    rc = pthread_create(&thread[i], NULL, mythread,arg);

    if(rc) {
      printf("Error creating threads\n");
      exit(-1);
    }

    sleep(1);

  }

  for(int i = 0; i<NUM_THREADS; i++) {
    rc = pthread_join(thread[i], NULL);

    if(rc) {
      printf("error joining threads\n");
      exit(-1);
    }
  }

  sem_destroy(&semaphore);

  return 0;
}
