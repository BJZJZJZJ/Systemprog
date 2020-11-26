#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void handler(int signo){

	printf("At handler : Wake up!\n");
}


int main(void){
	int i;

	sigset_t new;

	sigfillset(&new);
	sigdelset(&new, SIGINT);
	sigdelset(&new, SIGALRM);
	sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);

	signal(SIGALRM, handler);
	for (i = 0 ; i < 5; i++){
		alarm(2);
		printf("Pause ...\n");
		pause();
	}

	printf("Bye~\n");

	sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);


	return 0;
}
