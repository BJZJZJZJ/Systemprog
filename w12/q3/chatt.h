#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
	long mtype;
	char mtext[256];
};

struct msgbuf send_buf, recv_buf;
int send_msq, recv_msq;

void *send_thread(void* arg){
	while(1){
		memset(send_buf.mtext,'\0',sizeof(send_buf.mtext));
		printf("> ");
		fgets(send_buf.mtext, sizeof(send_buf), stdin);
		send_buf.mtext[strlen(send_buf.mtext)-1] = '\0';

		if(msgsnd(*(int*)arg, (void *)&send_buf, 256,IPC_NOWAIT) == -1){
			perror("msgsnd");
		}
		else{
			if( strcmp(send_buf.mtext, "/q") == 0 ){
				printf("### Finish Chatt ###\n");
				exit(0);
			}
			printf("%s : %s \n", SEND, send_buf.mtext);
		}
	}
}

void *recv_thread(void* arg){
	while(1){
		memset(recv_buf.mtext,'\0',sizeof(recv_buf.mtext));
		if(strcmp(RECV,"P2") == 0)
			msgrcv(*(int *)arg, &recv_buf, 256, 1, 0);
		else 
			msgrcv(*(int *)arg, &recv_buf, 256, 2, 0);
		printf("%s : %s\n", RECV, recv_buf.mtext);
		memset(recv_buf.mtext,'\0',sizeof(recv_buf.mtext));
	}
}

