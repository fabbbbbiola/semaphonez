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
        int fd = open("story.txt", O_CREAT | O_TRUNC | O_RDWR, 0644 );
	return fd;

}

void removal(int fd){
  	int semaphore;
  	semaphore = semget(SEMKEY,0,0);
	semctl(semaphore, 0, IPC_RMID);

	int shared_memory;
	shared_memory = shmget(SHMKEY,0,0);
	semctl(shared_memory, 0, IPC_RMID);

	struct stat st;
	stat("story.txt", &st);
	char *buffer;

	read(fd, buffer, st.st_size);
	printf("%s\n", buffer);

	remove("story.txt");
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


