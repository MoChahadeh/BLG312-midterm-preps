#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t lock;
int global_counter = 0;

void *my_thread(void* args) {

  int* index;

  index = (int *) args;

  int counter = 0;
  for(int i = 0; i<5; i++) {
    printf(".");
    counter++;
    fflush(stdout);
    sleep(1);
  }

  pthread_mutex_lock(&lock);
  printf("\nthread %d is counting...", index);
  global_counter += counter;
  sleep(1);
  pthread_mutex_unlock(&lock);

}

int main(int argc, char const *argv[]) {

  pthread_t thread[5];

  pthread_mutex_init(&lock, NULL);

  for(int i = 0; i< 5; i++) {

    int rc = pthread_create(&thread[i], NULL, my_thread, (void *) i);

    if(rc) {

        perror("pthread_Create");
        exit(1);

    }

  }


  for(int i = 0; i<5; i++) {

    int rc = pthread_join(thread[i], NULL);

    if(rc) {
      perror("Join error");
      exit(1);
    }

  }

  printf("\nglobal_counter: %d\n", global_counter);

  pthread_mutex_destroy(&lock);

  return 0;
}
