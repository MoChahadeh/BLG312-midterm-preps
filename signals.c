#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int sig) {

  if(sig == SIGINT) printf("\nSIGINT Signal Recieved!\n");
  else if (sig == SIGABRT) printf("\nSIGABRT Signal Recieved!\n" );

}

int main(int argc, char const *argv[]) {

  signal(SIGINT, handle_signal);
  signal(SIGABRT, handle_signal);

  while(1){

    printf("waiting for a signal...");
    sleep(1);

  }

  return 0;
}
