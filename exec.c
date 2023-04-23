#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {


  printf("Master: %d\n", getpid());
  int f = fork();

  if (f < 0) {
    printf("Error forking..\n");
    return 0;
  }
  else if(f == 0) {

    printf("This is child %d, transferring to slave...\n", getpid());

    execlp("./slave-exec", "./slave-exec", "test1", "\0");

    printf("\n %s", strerror(errno));

  } else {

    sleep(1);
    exit(0);

  }

  return 0;
}
