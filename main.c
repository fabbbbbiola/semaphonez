#include "semaphore.h"

int main(){
	int input_length = shmat(shared_memory, 0, 0);

	union semun semopts;
	semopts.val = 2;
	semctl( sephamore, 0, SETVAL, semopts);



	char input[256];
	printf("Input:\t");
	fgets(input, sizeof(input), stdin);
	printf("%s\n", input);

	int i = scanf(input);
}
