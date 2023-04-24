#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
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

  // wait for receiving message..

  printf("waiting to receive message..\n");

  int receive = msgrcv(msqid, &msg, sizeof(msg), 1, 0);

  if(receive == -1) {
    perror("Error receiving message..\n");
    exit(-1);
  }

  printf("MESSAGE RECEIVED!  %s\n", msg.mtext);

  sleep(2);

  msg.mtype = 2;
  strcpy((char *)msg.mtext, "Hello from second prog..\n");
  printf("Sending message..\n");
  int send = msgsnd(msqid, &msg, sizeof(msg), 0);

  if(send == -1) {
    perror("Error sending message...\n");
    exit(-1);
  }

  printf("message sent!\n");


  return 0;

}
