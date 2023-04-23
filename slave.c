#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"


int main(int argc, char const *argv[]) {
  /* code */

  printf("this is slave program of the exec.c program, pid: %d\n", getpid());
  printf("\t my parent is %d\n", getppid());
  printf("\t this is the first arg: %s \n", argv[1]);

  return 0;
}
