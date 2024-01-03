#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define  BUFSIZE    128

void signalHandler (int signo);

struct {
  long type;
  char data[BUFSIZE];
} msg_data = {1, "This is message queue sample"};

int msqid;

int main()
{
  /* return message queue, create message queue which have key 1234
     if exist message queue which had key 1234, return that messaeg queue id
   */
  if ((msqid = msgget((key_t) 1234, IPC_CREAT|0666)) == -1) {
    fprintf(stderr, "Message Queue get Failed\n");
    return 1;
  }
  
  // send msg_data message to message queue which have msgid
  if (msgsnd(msqid, &msg_data, strlen(msg_data.data), 0) == -1) {
    fprintf(stderr, "Message queue send Failed\n");
    return 1;
  }

  // set execute signalHandler when get SIGINT signal
  signal(SIGINT, signalHandler);
  pause();
}

void signalHandler(int signo) {
  // delete message queue
  if (msgctl(msqid, IPC_RMID, 0) == -1) {
    fprintf(stderr, "message queue control failed\n");
    exit(1);
  }

  exit(0);
}

