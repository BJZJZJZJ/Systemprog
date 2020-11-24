#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]){
	int fd, status;
	pid_t pid;
	caddr_t addr;
	struct stat statbuf;
	int random, i;

	if (stat("game.txt", &statbuf) == -1){
		perror("stat"); exit(1);
	}

	if ((fd = open("game.txt", O_RDWR)) == -1){
		perror("open"); exit(1);
	}

	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,
			MAP_SHARED, fd, (off_t)0);

	if (addr == MAP_FAILED){
		perror("mmap"); exit(1);
	}

	close(fd);


	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0 :
			for (i = 0 ; i < 100 ; i++){
				addr[(i % 50)] = 'c';				
				usleep(100000);
			}
			break;

		default : 
			srand(time(NULL));
			for (i = 0 ; i < 100 ; i++){
				random = (rand() % 100);
				addr[random] = 'p';
				usleep(100000);
			}
			wait(&status);
			printf("match ends\n");
			break;
	}
	return 0;	
}
