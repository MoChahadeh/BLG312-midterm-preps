#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

int myglobal;
pthread_mutex_t lock;

void* thread_function(void* arg) {

  int i, j;

  for(int i = 0; i< 20; i++)
   {
     pthread_mutex_lock(&lock);
     j= myglobal;
     j= j+1;
     printf(".");

     fflush(stdout);
     myglobal=j;
     pthread_mutex_unlock(&lock);
     sleep(1);
   }
   printf("\n");
   pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  /* code */

  pthread_t mythread;
  int i;
  myglobal = 0;

  if(pthread_mutex_init(&lock, NULL) != 0) {
    printf("mutex init failed\n");
    return 1;
  }

  if(pthread_create(&mythread, NULL, thread_function, NULL)) {
    printf("Thread creating failed..\n");
    abort();
    return 1;
  }

  for(int i = 0; i<20; i++ ) {
    pthread_mutex_lock(&lock);
    myglobal += 1;
    printf("o");
    fflush(stdout);
    pthread_mutex_unlock(&lock);
    sleep(1);
  }

  pthread_join(mythread, NULL);
  pthread_mutex_destroy(&lock);

  printf("\nglobal equals %d\n", myglobal);

  pthread_exit(NULL);
  return 0;
}
