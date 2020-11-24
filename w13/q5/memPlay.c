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

	if (argc != 2){
		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		exit(1);
	}

	if (stat(argv[1], &statbuf) == -1){
		perror("stat"); exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) == -1){
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
			srand(time(NULL)+35);
			for (i = 0 ; i < 100 ; i++){
				random = (rand() % 100);
				addr[random] = 'c';
				sleep(1);
			}
			break;

		default : 
			srand(time(NULL));
			for (i = 0 ; i < 100 ; i++){
				random = (rand() % 100);
				addr[random] = 'p';
				sleep(1);
			}
			wait(&status);
			printf("Match End!\n");
			break;
	}


	return 0;	
}
