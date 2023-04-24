#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {

  int pipefd[2];
  char buffer[128];
  int pid;

  if(pipe(pipefd) == -1) {
    perror("Error piping");
    exit(1);
  }

  pid = fork();

  if(pid == 0){ // Child Process

    close(pipefd[1]);
    read(pipefd[0], buffer, sizeof(buffer));
    printf("Child received: %s\n", buffer);
    close(pipefd[0]);

  }else { // parent process

    close(pipefd[0]);
    char *msg = "Hello Child!\0";
    write(pipefd[1], msg, sizeof(buffer));
    printf("Parent sent: %s\n", msg);
    close(pipefd[1]);
  }


  return 0;
}
