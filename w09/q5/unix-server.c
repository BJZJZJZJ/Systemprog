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

	printf("Connect Success!\n\n");
	

	
	// file path receive
	if(recv(ns, buf, sizeof(buf),0) == -1){
		perror("recv"); exit(1);
	}

	printf("Path : %s\n", buf);
	
	// open 
	if((fp = fopen(buf, "r")) == NULL){
		// send fail msg to client 
		sprintf(buf,"File not exist");	
		if(send(ns, buf, strlen(buf) +1,0) == -1){
			perror("send"); exit(1);
		}

		// Exception
		perror("fopen"); exit(1);
	}

	// calc file size (size > 1023 ??)
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);

	if(size > 1023)
		size = 1023;


	// read file
	fread(buf, sizeof(char)*size, 1, fp);
	buf[size+1]='\0';

	// send file text to client
	if(send(ns, buf, strlen(buf) +1,0) == -1){
		perror("send"); exit(1);
	}

	printf("bye\n");

	close(ns);
	close(sd);

	return 0;
}	

