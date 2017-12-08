#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SEMKEY 24601
#define SHMKEY 46902

int semaphore;
int shared_memory;
int file;


void creation(char *);
void removal();
void attach();
void control(int, char **);
