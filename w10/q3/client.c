#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) { 
	char buf[256];
	struct sockaddr_in sin; 
	int sd,n;

	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { 
		perror("socket"); exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin)); 
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(5061);

	strcpy(buf, "Time Request");
	if ((sendto(sd, buf, strlen(buf)+1, 0, (struct sockaddr *)&sin, sizeof(sin))) == -1){	
		perror("sendto");
		exit(1); 
	}

	n = recvfrom(sd, buf, 255, 0, NULL,NULL);
	buf[n]='\0';

	printf("** Server Time : %s\n", buf); 

	
	return 0;
}
