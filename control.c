#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#define KEY 24601

int main(int argc, char* argv[]) {

  if (!strcmp(argv[1], "-c") && argc > 2) {
    int sd = semget(KEY, 1, 0644 | IPC_CREAT | IPC_EXCL);
    if (sd < 0)
      printf("Semaphore already exists\n");
    else
      printf("Semaphore created: %d\nDefault value set: %d\n", sd, semctl(sd, 0, GETVAL));

    semctl(sd, 0, SETVAL, atoi(argv[2]));
  }

  else if(!strcmp(argv[1], "-v")) {
    int sd = semget(KEY, 1, 0644 | IPC_CREAT | IPC_EXCL);
    if (sd < 0) {
      sd = semget(KEY, 1, 0644 | IPC_CREAT);
      printf("Semaphore value: %d\n", semctl(sd, 0, GETVAL));
    }
    else {
      semctl(sd, 0, IPC_RMID);
      printf("Semaphone does not exist\n");
    }
  }

  else if(!strcmp(argv[1], "-r")) {
    int sd = semget(KEY, 1, 0644 | IPC_CREAT | IPC_EXCL);
    if (sd < 0) {
      sd = semget(KEY, 1, 0644 | IPC_CREAT);
      semctl(sd, 0, IPC_RMID);
      printf("Semaphore removed\n");
    }
    else {
      semctl(sd, 0, IPC_RMID);
      printf("Semaphone does not exist\n");
    }
  }
}
