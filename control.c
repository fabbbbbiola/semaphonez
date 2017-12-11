#include "semaphore.h"


int creation(){

	//Semaphore Interaction
  	int semaphore = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0600);
  	if(semaphore == -1){
    		printf("Semaphore already exists.\n\n");
  	}
  	else{
	    	union semun semopts;
		semopts.val = 1;
    		semctl(semaphore, 0, SETVAL, semopts);
  	}

	//Shared Memory Interaction
	int shared_memory = shmget(SHMKEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0600);
	if(shared_memory == -1){
		printf("Shared Memory already exists\n\n");
	}


	//File Interaction
        int fd = open("story.txt", O_CREAT | O_TRUNC | O_RDWR | O_APPEND, 0644 );
	return fd;

}

void view(){
        struct stat st;
        stat("story.txt", &st);
        char *buffer;

  	FILE *stream;
  	char my_file[]="story.txt";

  	fileno(stdin);

	int fd;
  	if ((stream = fopen(my_file, "w")) == NULL)
    		perror("fopen() error");
  	else {
    		fd = fileno(stream);
    		fclose(stream);
  	}

        read(fd, buffer, st.st_size);
        printf("%s\n", buffer);
}


void removal(){
        int semaphore = semget(SEMKEY,0,0);
        struct sembuf * operation = { -1, semaphore, SEM_UNDO};
        //Blocks until all other functions end
        semop(semaphore, operation, 1);
        semctl(semaphore, 0, IPC_RMID);

        int shared_memory;
        shared_memory = shmget(SHMKEY,0,0);
        semctl(shared_memory, 0, IPC_RMID);

        view();

        remove("story.txt");
}



int control(int argc, char ** argv){
	int used = 0;
	if(strcmp(argv[1], "-r") == 0){
      		removal();
		used = 1;
	}

    	if(strcmp(argv[1], "-v") == 0){
      		view();
		used = 1;
	}

    	if(strcmp(argv[1], "-c") == 0){
     		creation();
		used = 1;
	}
	return used;
}


