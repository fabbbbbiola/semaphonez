#include "semaphore.h"

int main(int argc, char ** argv){
	if (!control(argc, argv)){
       		struct sembuf * operation = { -1, semaphore, SEM_UNDO};
        	//Blocks until all other functions end
	        semop(semaphore, operation, 1);

		int input_length = shmat(SHMKEY, 0, 0);

		int fd = creation();
		char *last_input = (char*)malloc(input_length);
		read(fd, last_input , input_length);

		char input[256];
		printf("Input:\t");
		fgets(input, sizeof(input), stdin);
		int size = strlen(input);
		write(fd, input, size);

		printf("\nLast line:\n\n \t%s\n", input);

		shmdt(input_length);
	}
	return 0;
}
