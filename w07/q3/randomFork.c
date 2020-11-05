#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc , char *argv[]){
	int random;  int f; 		// f : fork
	int waitPid; int chk = 1;	// chk : is first parent?
	float prob = atof(argv[1]) * 100; 

	srand(time(NULL));

	printf("Probability = %f%%\n",prob);

	while((random = rand() % 100) < prob){ 
		f = fork();
	
		if(chk || f <= 0)  // first time or child process
			printf("My PID (%d), My Parent PID (%d)\n",getpid(), getppid());
		
		waitPid = wait(NULL);
		if(waitPid != -1)
			printf("Waited pid : %d\n",waitPid);

		chk = 0;
	}
	


	return 0;
}
