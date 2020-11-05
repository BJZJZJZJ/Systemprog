#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	sleep(atoi(argv[1]));
	return 0;
}
