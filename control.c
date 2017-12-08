#include "semaphore.h"


void creation(char * c){
    int ref;
    ref = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0600);
    if(ref == -1){
        printf("Semaphore already exists.\n\n");
    }
    else{
        int i = *c;
        semctl(ref, 0, SETVAL, i);
        printf("ID: %d, Value: %s. \n\n", ref, c);
    }
}

void removal(){
    int ref;
    ref = semget(KEY,0,0);
    printf("Removed sempahore: %d\n\n", semctl(ref, 0, IPC_RMID));
}

void attach(){
    int ref;
    ref = semget(KEY, 0,0);
    printf("Semaphore value is: %d \n\n", semctl(ref,0, GETVAL));
}


void control(int argc, char ** argv){
    if (argc < 2){
        printf("Not enough arguments. Failed.\n");
    }
    else{
        if(strcmp(argv[1], "-r") == 0)
            removal();

        if(strcmp(argv[1], "-v") == 0)
            attach();

        if(strcmp(argv[1], "-c") == 0)
            creation(argv[2]);


        else {
            printf("Invalid arguments. Please try again.\n");
        }
  }
}

