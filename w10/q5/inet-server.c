#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char buf[256];
	struct sockaddr_in sin,cli;
	int sd, ns[3], clientlen = sizeof(cli[0]);
	int cli_num = 0;
	int fds[2];
	
	pip(fds);

	if(argc != 3){
		printf("Please Enter 2 Arguments\n");
		printf("[1] : IP Address (*.*.*.*)\n");
		printf("[2] : Port Number\n");
		exit(1);
	}		

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(argv[2]));
	sin.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("bind"); exit(1);
	}

	printf("Wait....\n");

	if(listen(sd,10)){
		perror("listen"); exit(1);
	}
	

	while(1){
		if((ns[cli_num++] = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1){
			perror("accept"); exit(1);
		}
	
		printf("Client Connected!\n\n");

		
	}
	printf("Good bye\n");

	close(ns);
	close(sd);

	return 0;
}	

