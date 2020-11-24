#define SEND "P1"
#define RECV "P2"
#include "chatt.h"

int main(int argc, char** argv){
	pthread_t send_Thread, recv_Thread;
	int ret, status=0;

	key_t key = ftok("q1.key",1);
	key_t key2 = ftok("q2.key",2);

	send_msq = msgget(key, IPC_CREAT|0644);
	recv_msq = msgget(key, IPC_CREAT|0644);

	if (send_msq == -1 || recv_msq == -1){
		perror("msgget"); exit(1);
	}

	send_buf.mtype = 2;
	recv_buf.mtype = 2;
	
	ret = pthread_create(&send_Thread, NULL, send_thread, (void*)&recv_msq);
	if( ret < 0 ){
		perror("thread create error : ");
		exit(0);
	}

	ret = pthread_create(&recv_Thread, NULL, recv_thread, (void*)&send_msq);
	if( ret < 0){
		perror("thread create error : ");
		exit(0);
	}

	printf("### Join chatt!! ###\n");

	pthread_join(send_Thread, (void**)&status);
	pthread_join(recv_Thread, (void**)&status);
	return 0;
}
