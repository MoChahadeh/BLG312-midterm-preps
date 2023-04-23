#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>

void* print_message_function(void* ptr) {

  char *message;
  message = (char*) ptr;
  printf("\n %s \n", message);

  pthread_exit(NULL);

}

int main(int argc, char const *argv[]) {

  pthread_t thread1, thread2, thread3;

  char *message1 = "Hello";
  char *message2 = "World";
  char *message3 = "!..";

  if(pthread_create(&thread1, NULL, print_message_function, (void*) message1)){
    fprintf(stderr, "pthread_Create failure...\n");
    exit(-1);
  }
  if(pthread_create(&thread1, NULL, print_message_function, (void*) message2)){
    fprintf(stderr, "pthread_Create failure...\n");
    exit(-1);
  }
  if(pthread_create(&thread1, NULL, print_message_function, (void*) message3)){
    fprintf(stderr, "pthread_Create failure...\n");
    exit(-1);
  }

  pthread_exit(NULL);
  return 0;
}
