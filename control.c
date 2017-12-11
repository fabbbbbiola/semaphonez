#include "semaphore.h"


void creation(){

	//Semaphore Interaction
  	semaphore = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0600);
  	if(semaphore == -1){
    		printf("Semaphore already exists.\n\n");
  	}
  	else{
	    	union semun semopts;
		semopts.val = 2;
    		semctl(semaphore, 0, SETVAL, semopts);
    		printf("ID: %d \n\n", semaphore);
  	}

	//Shared Memory Interaction
	shared_memory = shmget(SHMKEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0600);
	if(shared_memory == -1){
		printf("Shared Memory already exists\n\n");
	}


	//File Interaction
        int fd = open("story.txt", O_CREAT | O_EXCL | O_RDWR | O_APPEND, 0644 );
	return fd;

}

void removal(){
  int semaphore;
  semaphore = semget(SEMKEY,0,0);
  printf("Removed sempahore: %d\n\n", semctl(semaphore, 0, IPC_RMID));
}

void attach(){
  int semaphore;
  semaphore = semget(SEMKEY, 0,0);
  printf("Semaphore value is: %d \n\n", semctl(semaphore,0, GETVAL));
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


