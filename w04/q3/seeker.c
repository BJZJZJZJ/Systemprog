#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	FILE *fp;	int size;  // file size
	long cnt = strtol(argv[3], NULL , 10);  // argv[3] = byte

	char c;	// fgetc 

	// file open
	fp = fopen(argv[1],"r");

	if(fp == NULL){
		printf("File Open Error\n");
		exit(1);
	}
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	
	// Start Point : argv[2]
	if (strcmp(argv[2], "begin") == 0)	// begin
		fseek(fp, 0, SEEK_SET);
	else if (strcmp(argv[2], "end") == 0)	// end
		fseek(fp, 0, SEEK_END);
	else if (strcmp(argv[2], "mid") == 0)	// mid
		fseek(fp, size/2, SEEK_SET);
	else if (strtol(argv[2], NULL,10) >= 0)	// positive Number
		fseek(fp, strtol(argv[2],NULL,10) , SEEK_SET);
	else if (strtol(argv[2], NULL,10) < 0)	// Negative Number
		fseek(fp, strtol(argv[2],NULL,10) , SEEK_END);

	// File Read	
	if (cnt > 0)
		while (cnt > 0){
			if(feof(fp)){
				fseek(fp,0,SEEK_SET);
				continue;
			}

			c = fgetc(fp);
			printf("%c",c);
			cnt--;
		}
		
	
	else if (cnt < 0){
		cnt = -cnt;
		while (cnt > 0){
			if(ftell(fp) == 0)
				fseek(fp,-1,SEEK_END);
			c = fgetc(fp);
			fseek(fp,-2,SEEK_CUR);	

			printf("%c",c);
			cnt--;
		}
	}
	printf("\n");
	fclose(fp);
	return 0;
}
