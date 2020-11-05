#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <getopt.h>



int main(int argc, char *argv[]){
	int n;
	struct utsname uts;

	if (uname(&uts) == -1){
		perror("uname");
		exit(1);
	}

	if (argc == 1){
		printf("systemSummary - available options:\n");
		printf("-s : print OS name\n");
		printf("-n : print hostname\n");
		printf("-v : print OS version\n");
		printf("-m : print HW info\n");
		exit(1);
	}


	while((n = getopt(argc,argv,"snvm")) != -1){
		switch (n){
			case 'm':
				printf("HW info: %s\n", uts.machine);
				break;
			case 'v':
				printf("OS version: %s\n", uts.version);
				break;
			case 's':
				printf("OS name: %s\n",uts.sysname);
				break;
			case 'n':
				printf("hostname: %s\n", uts.nodename);
				break;
		}
	}


	return 0;
}
