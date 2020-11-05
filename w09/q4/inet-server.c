#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void){
	char buf[256];
	struct sockaddr_in sin,cli;
	int sd, ns, clientlen = sizeof(cli);
	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(15500);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("bind"); exit(1);
	}

	if(listen(sd,10)){
		perror("listen"); exit(1);
	}
	
	if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) ==-1){
		perror("accept"); exit(1);
	}
	
	while(1){
	
		if(recv(ns, buf, sizeof(buf),0) == -1){
			perror("recv"); exit(1);
		}

		printf("Msg : %s\n", buf);

		if(buf[0] == 'q' && buf[1] == '\0')
			break;
	
		sprintf(buf, "Server Received the message!\n");
		if(send(ns, buf, strlen(buf) +1,0) == -1){
			perror("send"); exit(1);
		}
	}

	printf("Good bye\n");

	close(ns);
	close(sd);

	return 0;
}	

