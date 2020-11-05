#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/un.h>

int main(void){
	char buf[1024];
	struct sockaddr_un ser;
	int sd, len;

	initscr();

	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("sokcet"); exit(1);
	}

	// socket setting
	memset((char *)&ser, '\0',sizeof(ser));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path, "hsocket");
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);


	if(connect(sd, (struct sockaddr *)&ser, sizeof(ser))){
		perror("connect"); exit(1);
	}

	
	// input file path
	printw("File path : ");
	scanw("%s",buf);

	if(send(sd, buf, strlen(buf) +1,0) == -1){
		perror("send"); exit(1);
	}

	// file text receive
	if(recv(sd, buf, sizeof(buf),0) == -1){
		perror("recv"); exit(1);
	}

	printw("file text : %s\n", buf);
	
	refresh();
	
	printw("\nGood bye\n");
	refresh();

	sleep(5);

	close(sd);
	endwin();

	return 0;
}	

