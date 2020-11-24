#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

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

	printf("%s\n",buf);

	if((opd = open(buf,O_RDONLY)) == -1){
		write(wpd,"<ERROR> No such file\n");
		close(wpd);
		perror("open"); exit(1);
	}

	n = read(opd, buf, sizeof(buf));
	buf[n]='\0';
	printf("%s\n",buf);
	write(wpd, buf, 128);

	close(wpd);
	close(opd);


	return 0;
}
