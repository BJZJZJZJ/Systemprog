#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>

int main(int argc, char *argv[]){
	time_t t;
	char buf[256];
	char host[128];
	struct sockaddr_in sin,cli;
	int sd, ns, clientlen = sizeof(cli);

	

	char msg[] = "<Available Services>\
		\n1.Echo server <ECHO>\
		\n2.Get server info <SINFO>\
		\n3.Get server time <STIME>\n";
		
		

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(7073);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("bind"); exit(1);
	}

	printf("Wait....\n");

	if(listen(sd,10)){
		perror("listen"); exit(1);
	}

	while(1){	
		if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) ==-1){
			perror("accept"); exit(1);
		}

		// Service info Message
		if(send(ns, msg, sizeof(msg),0) == -1){
			perror("send"); exit(1);
		}

		// get Request
		if(recv(ns, buf, sizeof(buf), 0) ==-1 ){
			perror("recv"); exit(1);
		}


		if(strcmp("ECHO",buf) == 0){
			printf("ECHO REQUEST\n");
			switch(fork()){
				case 0:
					close(sd);
					while(1){
						if(recv(ns,buf,sizeof(buf),0)==-1){
							perror("recv"); exit(1);
						}
						printf("Client : %s\n",buf);

						if(strcmp(buf,"QUIT") == 0){
							close(ns);
							exit(0);
						}

						if(send(ns,buf,sizeof(buf),0)==-1){
							perror("send"); exit(1);
						}
	
					}
			}
		}

		else if(strcmp("SINFO",buf)==0){
			printf("SINFO REQUEST\n");
			switch(fork()){
				case 0:
					close(sd);
					gethostname(host,128);
					sprintf(buf,"Host Name : %s\nPort : %d\nIP : %s\n"
						,host,ntohs(sin.sin_port),inet_ntoa(sin.sin_addr));
					if(send(ns,buf,sizeof(buf),0)==-1){
						perror("send"); exit(1);
					}

					close(ns);
					exit(0);

			}
		}
		else if(strcmp("STIME",buf)==0){
			printf("STIME REQUEST\n");
			switch(fork()){
				case 0:
					close(sd);
					time(&t);
					sprintf(buf,"%s",ctime(&t));
	
					if(send(ns,buf,sizeof(buf), 0) == -1 ) {
						perror("send"); exit(1);
					}
					close(ns);
					exit(0);
			}
		}
		else {
			sprintf(buf,"** Incorrect Value **\n");
			if(send(ns,buf,sizeof(buf),0) == -1) {
				perror("send"); exit(1);
			};
		}

		close(ns);
	}

	close(sd);

	return 0;
}	

