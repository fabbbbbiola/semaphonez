#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SEMKEY 24601
#define SHMKEY 46902

void creation();
void removal();
void attach();
void control(int, char **);
