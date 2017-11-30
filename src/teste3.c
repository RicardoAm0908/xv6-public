#include "types.h"
#include "stat.h"
#include "syscall.h"
#include "user.h"

#define IS_FORKED (pid == 0)
#define CHECK_FORK() if (pid < 0) printf(1, "Fork failed!");

#define LIMIT 500
#define N 10

int tickets[N] = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2};

void losttime();

void nop() {
  // Must do something like "print nothing" due agressive loop optimizations
  printf(1, "");
  return;
}

int main()
{
  int pid = 0;
  unsigned int i;

  printf(1, "\nI'm PID %d, the great and powerful father\n\n", getpid());

  pid = fork(tickets[0]);
  CHECK_FORK();

  for(i = 1; i < N; i++) {
      if(!IS_FORKED) {
        pid = fork(tickets[i]);
        CHECK_FORK();
      }
  }

  if (pid == 0) {
    printf(1, "PID %d has started with %d tickets\n", getpid(), gettickets());
    losttime();
    printf(1, "PID %d has ended!\n", getpid());
  }

  while (1) {
    pid = wait();
    if (pid < 0) break;
  }
  exit();
}

void losttime() {
  unsigned int i, j, k;

  for (i = 0; i < LIMIT; i++)
    for (j = 0; j < LIMIT; j++)
      for (k = 0; k < LIMIT; k++)
        //for(l = 0; l < LIMIT; l++)
          //for(m = 0;// m < LIMIT; m++)
            nop();
}
