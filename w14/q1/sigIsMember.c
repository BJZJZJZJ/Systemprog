#include <signal.h>
#include <stdio.h>


int main(void){
	sigset_t st;

	sigfillset(&st);

	if(sigismember(&st, SIGBUS))
		printf("SIGBUS is set\n");
	else
		printf("SIGBUS is not set\n");


	return 0;
}
