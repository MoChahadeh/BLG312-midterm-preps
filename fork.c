#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {

  int f = fork();

  if(f < 0) {
    printf("Error forking");
  }
  else if(f == 0){
    sleep(1);
    printf("Child process pid: %d\n", getpid());
    sleep(5);
    printf("\t and parent is pid: %d\n", getppid());


  }else {
    printf("Parent process pid: %d \n", getpid());
    wait(NULL);
    printf("parent process terminating...");
  }

  return 0;
}
