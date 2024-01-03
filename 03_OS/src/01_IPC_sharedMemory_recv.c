#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>

#define BUFSIZE 1024

int main()
{
  struct check_data {
    int check;
    char data[BUFSIZE];
  } *shared_data;

  int shmid;
  char *shmaddr;
  char buffer[BUFSIZE];

  if ((shmid = shmget((key_t) 1234, BUFSIZE, IPC_CREAT|0666)) == -1) {
    fprintf(stderr, "Failed to create shared memory\n");
    exit(1);
  }

  if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1) {
    fprintf(stderr, "Failed to attach shamred memory\n");
    exit(1);
  }

  shared_data = (struct check_data *) shmaddr;

  while(1) {
    while (shared_data->check) {
      sleep(1);
      printf("Waiting...\n");
    }

    printf("input data ===> ");
    fgets(buffer, BUFSIZE, stdin);

    strncpy(shared_data->data, buffer, BUFSIZE);
    shared_data->check = 1;

    if (!strncmp(shared_data->data, "quit", 4)) 
      break;
  }

  if (shmdt(shmaddr) == -1) {
    fprintf(stderr, "Failed to detach shared memory\n");
    exit(1);
  }

  return 0;
}
