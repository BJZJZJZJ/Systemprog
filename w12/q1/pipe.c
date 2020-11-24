#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	FILE *fp;
	int fd, pid;

	fp = popen("grep sys" , "w");
	if(fp == NULL){
		fprintf(stderr, "popen failed\n");
		exit(1);
	}

	pid = fork();

	if(pid == 0){	
		close(1);
		fd = dup(fileno(fp));
		execl("/bin/ps","ps","-ef",(char *)NULL);
	}


	pclose(fp);

	return 0;
}
