#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
	char *val;

	val = getenv(argv[1]);

	

	if(strstr(val, argv[2]) != NULL){
		printf("%s has %s!\n",argv[1],argv[2]);	
	}
	else{
		printf("%s does not have %s...\n" ,argv[1],argv[2]);
	}

	return 0;
}
