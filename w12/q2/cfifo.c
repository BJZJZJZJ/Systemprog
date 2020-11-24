#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(){
	int opd, wpd, n;
	char buf[128];
	char filename[30];
	char download[30] = "download_";

	/*
	if (mkfifo("./A-FIFO",0666) == -1){
		perror("mkfifo");  exit(1);
	}
	*/

	if((wpd = open("./A-FIFO",O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}
	printf("Filename : ");
	scanf("%s",filename);


	write(wpd,filename,strlen(filename)+1);
	close(wpd);

	if((opd = open("./A-FIFO",O_RDONLY)) == -1){
		perror("open");  exit(1);
	}

	strcat(download,filename);

	read(opd, buf, 128);
	if(strstr(buf,"<ERROR>") == NULL){
		if((wpd = open(download, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1){
			perror("open"); close(opd); exit(1);
		}
		write(wpd, buf, strlen(buf));
		close(wpd);
	}
	else{
		printf("%s\n",buf);
		printf("File doen not exist!\n");
	}

	close(opd);


	return 0;
}
