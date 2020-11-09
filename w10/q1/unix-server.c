#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>


int main(void){
	char buf[1024];
	struct sockaddr_un ser,cli;
	int sd, ns, len, clen = sizeof(cli);
	int size;	FILE *fp;
	
	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}

	memset((char *)&ser, '\0',sizeof(ser));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path, "hsocket");
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);


	if(bind(sd, (struct sockaddr *)&ser, len)){
		perror("bind"); exit(1);
	}

	printf("Wait....\n");

	if(listen(sd,10)){
		perror("listen"); exit(1);
	}
	
	if((ns = accept(sd, (struct sockaddr *)&cli, &clen)) ==-1){
		perror("accept"); exit(1);
	}

	printf("Client Connected! \n\n");


	while(1){
		if(recv(ns, buf, sizeof(buf),0) == -1){
			perror("recv"); exit(1);
		}
	
		printf("YOU : %s\n", buf);

		if(strcmp(buf,"QUIT") == 0) break;
		

		printf("ME : ");
		scanf("%s",buf);

		// send file text to client
		if(send(ns, buf, strlen(buf) +1,0) == -1){
			perror("send"); exit(1);
		}

		if(strcmp(buf,"QUIT") == 0) break;

	}

	printf("bye\n");

	close(ns);
	close(sd);

	return 0;
}	
