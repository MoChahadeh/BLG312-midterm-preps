#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {

  long mtype;
  char mtext[100];

};

int main(){

  key_t key;
  struct message msg;

  key = ftok(".", 1);

  // create a message queue
  int msqid = msgget(key, IPC_CREAT|0777);

  if(msqid == -1) {
    perror("Error creating msg queue..\n");

    exit(-1);
  }

  //send message to queue
  msg.mtype = 1;
  strcpy(msg.mtext, "Hello from program 1");
  int send = msgsnd(msqid, &msg, sizeof(msg), 0);

  if(send == -1) {
    perror("Error sending message\n");
    exit(-1);
  }

  printf("message sent...\n");

  sleep(3);

  printf("Waiting for message to receive..\n");
  int receive = msgrcv(msqid, &msg, sizeof(msg), 2, 0);

  if(receive == -1) {
    perror("Error receiving message\n");
    exit(-1);
  }

  printf("message received!\n%s\n", msg.mtext);

  return 0;

}
