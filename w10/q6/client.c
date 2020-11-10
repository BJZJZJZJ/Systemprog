#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ncurses.h>

int main(int argc, char *argv[]){
	char buf[256];
	struct sockaddr_in sin;
	int sd;

	initscr();
	start_color();

	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);


	if(argc != 3){
		printw("Please Enter 2 Arguments\n");
		printw("[1] : IP Address (*.*.*.*)\n");
		printw("[2] : Port Number\n");
		refresh();
		sleep(3);
		endwin();
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
		attron(COLOR_PAIR(1));
		printw("ME : ");
		scanw("%s",buf);
		refresh();

		if(send(sd, buf, strlen(buf) +1,0) == -1){
			perror("send"); exit(1);
		}

		if(strcmp(buf,"QUIT") == 0) break;


		if(recv(sd, buf, sizeof(buf),0) == -1){
			perror("recv"); exit(1);
		}
	
		attron(COLOR_PAIR(2));
		printw("YOU : %s\n", buf);
		refresh();
		if(strcmp(buf,"QUIT") == 0) break;
	}

	printw("Good bye\n");
	close(sd);

	endwin();

	return 0;
}	
