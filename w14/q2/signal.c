#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo){
	printf("SIGQUIT handler is called!\n");
}



int main(void){
	void (*hand)(int);

	hand = signal(SIGQUIT, handler);
	if (hand == SIG_ERR){
		perror("signal"); exit(1);
	}

	pause();

	return 0;
}
