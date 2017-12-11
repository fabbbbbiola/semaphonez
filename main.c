#include "semaphore.h"

int main(int argc, char ** argv){
	if (!control(argc, argv)){
	        int semaphore = semget(SEMKEY, 1, 0644);
       		struct sembuf * operation = { -1, semaphore, SEM_UNDO};
        	//Blocks until all other functions end
	        semop(semaphore, operation, 1);

		int input_length = shmat(SHMKEY, 0, 0);

		int fd = creation();
		char *last_input = (char*)calloc(256, input_length);
		lseek(fd, -1 * input_length, SEEK_END);
		read(fd, last_input, input_length);
		printf("Last line: %s\n", last_input);
		
		char input[256];
		printf("Input:\t");
		fgets(input, sizeof(input), stdin);
		int size = strlen(input);
		write(fd, input, size);
		
		shmdt(input_length);
		close(fd);
		operation->sem_op = 1;
		semop(semaphore, operation, 1);
	}
	else {
	  control(argc, argv);
	}
	return 0;
}
