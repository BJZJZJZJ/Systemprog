#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc , char* argv[])
{
	int n; 		// Option Value
	int i = 0, j;   // i : Encryption Value  ,  j : loop Index

	int file1;  int file2;
	char buf[10];	// buf

	extern int optind;  	
	extern char *optarg;

	if(argc != 3 && argc != 5){
	   printf("Wrong Argument\n");
	   exit(1);
	}
	// -c Option Check
	while((n = getopt(argc,argv,"c:")) != -1){
	   switch(n)
		case 'c':
		   i = atoi(optarg);  // Update  i
		   break;
	}
	
	// File Open
	file1 = open(argv[optind], O_RDONLY);
	file2 = open(argv[optind+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if(file1 == -1 || file2 == -1){
		printf("File Open Failed\n");
	}

	// File Copy & Paste & Encryption
	while((n = read(file1, buf, 4)) > 0){
		for (j = 0; j < 4 ; j++)
			buf[j] = buf[j] + i;
		if(write(file2, buf,n) !=n) printf("Write Error");
	}
	close(file1);
	close(file2);

	return 0;
}
