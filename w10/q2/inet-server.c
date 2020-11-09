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
	int sd, ns, clientlen = sizeof(cli);
	

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
	
	if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) ==-1){
		perror("accept"); exit(1);
	}

	printf("Client Connected!\n\n");
	
	while(1){
		if(recv(ns, buf, sizeof(buf),0) == -1){
			perror("recv"); exit(1);
		}

		printf("YOU : %s\n", buf);

		if(strcmp(buf,"QUIT")==0) break;
	
		printf("ME : ");
		scanf("%s",buf);
		
		if(send(ns, buf, strlen(buf) +1,0) == -1){
			perror("send"); exit(1);
		}

		if(strcmp(buf,"QUIT")==0) break;
	}

	printf("Good bye\n");

	close(ns);
	close(sd);

	return 0;
}	

