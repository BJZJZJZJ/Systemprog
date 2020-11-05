#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc , char* argv[])
{
	int n; 		// Option Value
	int i = 0;	// i : Decryption Value

	FILE *file1; FILE *file2;

	extern int optind;  	
	extern char *optarg;

	if(argc != 3 && argc != 5){
	   printf("Wrong Argument\n");
	   exit(1);
	}

	// -d Option Check
	while((n = getopt(argc,argv,"d:")) != -1){
	   switch(n)
		case 'd':
		   i = atoi(optarg);  // Update  i
		   break;
	}

	// File Open
	file1 = fopen(argv[optind], "r");
	file2 = fopen(argv[optind+1], "w");
	if( file1 == NULL || file2 == NULL ){
		printf("File Open Failed\n"); exit(1);
	}

	// File Copy & Paste & Decryption
	while((n = fgetc(file1)) != EOF){
		fputc(n-i,file2);
	}

	fclose(file1);
	fclose(file2);

	return 0;
}
