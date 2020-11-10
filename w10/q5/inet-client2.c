#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char buf[256];
	struct sockaddr_in sin;
	int sd;


	if(argc != 4){
		printf("Please Enter 3 Arguments\n");
		printf("[1] : IP Address (*.*.*.*)\n");
		printf("[2] : Port Number\n");
		printf("[3] : Name\n");
		exit(1);
	}

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}


	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(argv[2]));
	sin.sin_addr.s_addr = inet_addr(argv[1]);


	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("connect"); exit(1);
	}

	while(1){	
		if(recv(sd, buf, sizeof(buf),0) == -1){
			perror("recv"); exit(1);
		}
	}

	printf("Good bye\n");
	close(sd);

	return 0;
}	

