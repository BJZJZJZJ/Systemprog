#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	FILE *fp;

	if(mkdir(argv[1],0755) == -1){
		printf("Fail to Create Directory\n");
		exit(1);
	}

	chdir(argv[1]);

	fp = fopen("README.TXT","w");
	fclose(fp);

	return 0;
}


