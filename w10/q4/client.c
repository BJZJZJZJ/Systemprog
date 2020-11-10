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


	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}


	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(7073);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");


	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("connect"); exit(1);
	}


	if(recv(sd, buf, sizeof(buf),0) == -1){
		perror("recv"); exit(1);
	}
	printf("%s",buf);


	printf("\nEnter the Service : ");
	scanf("%s",buf);
	
	if(send(sd,buf, sizeof(buf),0) ==-1) {
		perror("send"); exit(1);
	}


	if(strcmp(buf,"ECHO") == 0){
		while(1){		
			printf("Msg : ");
			scanf("%s",buf);
			if(send(sd,buf,sizeof(buf),0)==-1){
				perror("send"); exit(1);
			}

			if(strcmp(buf,"QUIT") ==0){
				break;
			}

			if(recv(sd,buf,sizeof(buf),0)==-1){
				perror("recv"); exit(1);
			}

			printf("Server : %s\n",buf);
		}
	}
	
	else if(strcmp(buf,"SINFO") == 0){
		if(recv(sd,buf,sizeof(buf),0) == -1 ){
			perror("recv"); exit(1);
		}

		printf("%s",buf);
	}
	
	else if(strcmp(buf,"STIME") == 0){
		if(recv(sd,buf,sizeof(buf),0)==-1){
			perror("recv"); exit(1);
		}
		printf("Server Time : %s\n", buf);
	}

	else{
		if(recv(sd,buf,sizeof(buf),0)==-1){
			perror("recv"); exit(1);
		}
		printf("%s",buf);
	}

	close(sd);
	return 0;
}	

