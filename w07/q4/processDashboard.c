#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[]){
	int f;


	f = fork();
	
	if(f > 0){

	}
	else if (f = 0){
		
	}
	else {
		printf("fork fail\n");
	}
		


	return 0;
}
