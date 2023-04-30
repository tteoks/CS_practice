#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char **argv)
{
	int fd[2], nbytes, rc = 0;
	pid_t childpid;
  char sendbuf[1024] = {0, };
  char readbuf[1024] = {0, };

  printf("Example for Anonymouse PIPE\n");

  if ((rc = pipe(fd)) < 0)
    printf("ERROR: Creating PIPE [%d]\n", rc);

  if ((childpid = fork()) == -1) {
    printf("ERROR: Failed to fork\n");
    return 0;
  }
  printf("\nPID: %d\n", childpid);

  snprintf(sendbuf, sizeof(sendbuf), "This is Anonymouse PIPE test");  

  if (childpid == 0) {
    close(fd[0]);

    printf("[%d] Write msg pipe writer(Child)\n", childpid);
    write(fd[1], sendbuf, strlen(sendbuf));

    return 0;
  } else {
    close(fd[1]);

    printf("[%d] Read msg pipe reader(Parent)\n", childpid);
    nbytes = read(fd[0], readbuf, sizeof(readbuf));
    printf("\n[%d] Received parent string: \"%s\" \n", nbytes, readbuf);

  }

  return 0;

}
