#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	int address = strtol(argv[1],NULL,10);

	printf("address : %d\n",address);

	return 0;
}
