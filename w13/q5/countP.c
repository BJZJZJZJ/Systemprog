#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc , char *argv[]){
	int fd, i;
	int c=0, p=0;
	char buf[101];

	if (argc != 2){
		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) == -1){
		perror("open"); exit(1);
	}

	read(fd,buf,100);
	buf[100] = '\0';

	for(i = 0; i < 100; i++){
		if (buf[i] == 'c') c++;
		else if (buf[i]=='p') p++;
	}
	
	printf("Result : %s\n\n",buf);
	printf("p : %d ....  c : %d\n",p,c);

	if(p > c)
		printf("Parent won!\n");
	else if (p < c)
		printf("Child won!\n");
	else 
		printf("Even!\n");



	return 0;	
}

