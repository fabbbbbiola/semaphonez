#include "semaphore.h"

int main(){
	int input_length = shmat(shared_memory, 0, 0);

	union semun semopts;
	semopts.val = 2;
	semctl( semaphore, 0, SETVAL, semopts);

	int fd = open("story.txt", O_RDWR | O_APPEND, 0644 );
	char *last_input = (char*)malloc(input_length);
	read(fd, last_input , input_length);

	char input[256];
	printf("Input:\t");
	fgets(input, sizeof(input), stdin);
	int size = strlen(input);
	write(fd, input, size);

	printf("\nLast line:\n\n \t%s\n", input);

	shmdt(input_length);

	return 0;


}
