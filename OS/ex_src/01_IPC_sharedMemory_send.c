#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
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
  struct shmid_ds shm_stat;

  // Create shamred memory with key 1234
  if ((shmid = shmget((key_t)1234, sizeof(struct check_data), IPC_CREAT|0666)) == -1) {
    fprintf(stderr, "Shared Memroy create failed\n");
    exit(1);
  }

  // set shared memory call process into memory
  if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1) {
    fprintf(stderr, "Shared Memory get failed\n");
    exit(1);
  }

  // if check is 0, then no data in shared memory
  shared_data = (struct check_data *)shmaddr;
  shared_data->check = 0;

  while (1) {
    // success get data from shared memory
    if (shared_data -> check) {
      printf("data read from shared memroy: %s\n", shared_data->data);
      sleep(1);
      shared_data->check = 0;

      // stop process when get data "quit"
      if (!strncmp(shared_data->data, "quit", 4)) {
        // save shmid shared memory data into shm_stat
        if (shmctl(shmid, IPC_STAT, &shm_stat) == -1) {
          fprintf(stderr, "Shared memory control failed\n");
          exit(1);
        }

        // break looop when process in one in shared memory
        if (shm_stat.shm_nattch == 1)
          break;
      }
    }
    sleep (1);
  }

  // detach shared memory call process from memory
  if (shmdt(shmaddr) == -1) {
    fprintf(stderr, "Shared memory detach failed\n");
    exit(1);
  }

  // Delete shared memory
  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    fprintf(stderr, "Shared memoery delete failed\n");
    exit(1);
  }

  return 0;

}
