#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ncurses.h>


int main(void){
	char buf[256];
	struct sockaddr_in sin;
	int sd;


	initscr();

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}


	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(15500);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");


	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("connect"); exit(1);
	}

	while(1){	
		printw("to Msg : ");
		scanw("%s",buf);


		if(send(sd, buf, strlen(buf) +1,0) == -1){
			perror("send"); exit(1);
		}

		if(buf[0] == 'q' && buf[1] == '\0')
			break;


		if(recv(sd, buf, sizeof(buf),0) == -1){
			perror("recv"); exit(1);
		}
	
		printw("Msg : %s\n", buf);

		refresh();
	}

	printw("Good bye\n");

	close(sd);

	endwin();

	return 0;
}	

