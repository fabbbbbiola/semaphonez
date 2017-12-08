#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char input[256];
  printf("Input:\t");
  fgets(input, sizeof(input), stdin);
  printf("%s\n", input);
  
  int i = scanf(input);
  //  shmat( , &, );
}
