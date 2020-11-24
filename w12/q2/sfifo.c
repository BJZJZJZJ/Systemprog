#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int opd, wpd, n;
	char buf[128];

	/*
	if (mkfifo("./A-FIFO",0666) == -1){
		perror("mkfifo");  exit(1);
	}
	*/

	if((opd = open("./A-FIFO",O_RDONLY)) == -1){
		perror("open");  exit(1);
	}

	printf("Recieve Msg\n");
	while((n=read(opd, buf, 80)) > 0){
		printf("  - %s\n",buf);
	}
	close(opd);

	if((wpd = open("./A-FIFO",O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}
	printf("-----------\n");

	if((access( buf, F_OK)) != -1){
		if((opd = open(buf,O_RDONLY)) == -1){
			perror("open"); exit(1);
		}
	
		n = read(opd, buf, 128);
		buf[n]='\0';

		printf("File Send to Client\n");
		printf("%d\n",(int)strlen(buf));
		write(wpd, buf, strlen(buf));

		close(opd);
	}
	else {
		printf("Error Send\n");
		write(wpd,"<ERROR>",8); 
		close(wpd);
		exit(1);
	}

	close(wpd);

	return 0;
}
