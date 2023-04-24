#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {

  int shmid;
  key_t key;
  char *shm, *s;

  key = ftok(".", 1);

  shmid = shmget(key, SHM_SIZE, 0666);

  if(shmid < 0) {
    perror("shmget error");
    exit(-1);
  }

  shm = shmat(shmid, NULL, 0);

  printf("the data in memory: %s\n", shm);

  if(shmdt(shm) < 0){
    perror("shmdt error");
    exit(-1);
  }


  return 0;
}
