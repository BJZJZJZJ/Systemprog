#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){
	struct stat buf;
	FILE *fp1 , *fp2;
	int c;

	if (argc != 3){
		printf("Wrong argument!\n");
		exit(1);
	}

	stat(argv[2],&buf);
	fp1 = fopen(argv[1] , "r");

	if(fp1 == NULL){
		printf("File open fail");
		exit(1);
	}

	// if argv[2] : Directory
	if((buf.st_mode & S_IFMT) == S_IFDIR){
		chdir(argv[2]);
		fp2 = fopen(argv[1], "w");

		// Copy & Paste
		while((c = fgetc(fp1)) != EOF)
			fputc(c,fp2);

		// Remove origin file
		chdir("..");  unlink(argv[1]);

	}
	// Not Directory
	else
	{
		// Copy & Paste
		fp2 = fopen(argv[2],"w");
		while((c = fgetc(fp1)) != EOF)
			fputc(c,fp2);

		// Remove Origin file
		unlink(argv[1]);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
