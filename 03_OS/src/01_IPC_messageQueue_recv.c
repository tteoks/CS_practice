#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define BUFSIZE 128

struct {
  long type;
  char data[BUFSIZE];
} msg_data;

int main()
{
  int msqid;
  struct msqid_ds msg_stat;

  if ((msqid = msgget((key_t) 1234, IPC_CREAT|0666)) == -1) {
    fprintf(stderr, "Message Queue get failed\n");
    exit(1);
  }

  if (msgrcv(msqid, &msg_data, BUFSIZE, 0, 0) == -1) {
    fprintf(stderr, "Message queue recieve failed\n");
    exit(1);
  }

  printf("data read from message queue: %s\n", msg_data.data);
  if (msgctl(msqid, IPC_STAT, &msg_stat) == -1) {
    fprintf(stderr, "Message Queue control failed\n");
    exit(1);
  }

  kill(msg_stat.msg_lspid, SIGINT);

  return 0;

}

