#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // sleep


int main(void){
	int random;

	srand(time(NULL));
	random = (rand() % 21) + 10;  // (0~20) + 10

	printf("Hello world begins (r : %d)\n",random);
	sleep(random);
	printf("Hello world ends\n");

	return 0;
}
