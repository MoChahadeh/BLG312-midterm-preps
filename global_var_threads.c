#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

int global_int;

void* thread_function(void *arg) {

  int i,j;

  printf("\nglobal int at the start: %d\n", global_int);
  for(i = 0; i< 5; i++) {

    global_int++;

    printf(".");
    fflush(stdout);

    sleep(1);
  }

  printf("global int at the end: %d\n", global_int);
  printf("\n");
  pthread_exit(NULL);

}



int main(int argc, char const *argv[]) {

  pthread_t thread[3];
  int rc;
  global_int = 0;

  for(int i = 0; i<3; i++) {

    rc = pthread_create(&thread[i], NULL, thread_function, NULL);

    if(rc){
      printf("error creating thread %d\n", rc);
      exit(-1);
    }

  }

  // for(int i = 0; i<5; i++) {
  //   fflush(stdout);
  //   sleep(1);
  // }

  printf("Global int: %d\n", global_int);
  printf("Main completed\n");
  pthread_exit(NULL);
  return 0;
}
