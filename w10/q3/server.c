#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void) { 
	time_t t;
	char buf[256];
	struct sockaddr_in sin, cli; 
	int sd, clientlen = sizeof(cli);


	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { 
		perror("socket"); exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin)); 
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(5061);

	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("bind");
		exit(1);
	}

	while (1) {
		if ((recvfrom(sd, buf, 255, 0, (struct sockaddr *)&cli, &clientlen)) == -1) {
			perror("recvfrom"); exit(1);
		}
		
		time(&t);
		printf("** From Client : %s\n", buf); 
		strcpy(buf, ctime(&t));
		if ((sendto(sd, buf, strlen(buf)+1, 0, (struct sockaddr *)&cli, sizeof(cli))) == -1){	
			perror("sendto");
			exit(1); 
		}
	}
	return 0;
}
