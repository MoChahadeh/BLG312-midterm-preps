#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

  sem_t *shared_sem = sem_open("/my_semaphore", O_CREAT, 0666, 1);
  printf("Waiting for semaphore...\n");
  sem_wait(shared_sem);

  printf("Using semaphore....\n");
  sleep(10);

  sem_post(shared_sem);
  sleep(1);

  int sem_val;
  sem_getvalue(shared_sem, &sem_val);
  if(sem_val) sem_unlink("/my_semaphore");
  return 0;
}
