#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/shm.h>
#include <string.h>
#include <signal.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};


int initsem(key_t semkey){
	union semun semunarg;
	int status = 0, semid;

	semid = semget(semkey, 1 , IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1){
		if (errno == EEXIST){
			semid = semget(semkey, 1, 0);
		}
	}

	else {
		semunarg.val = 1;
		status = semctl(semid, 0, SETVAL, semunarg);
	}

	if(semid == -1 || status == -1){
		perror("initsem"); return(-1);
	}


	return semid;
}


int semlock(int semid){
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;

	if(semop(semid, &buf, 1) == -1){
		perror("semlock failed"); exit(1);
	}
	return 0;
}


int semunlock(int semid){
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = SEM_UNDO;

	if(semop(semid, &buf, 1) == -1){
		perror("semlock failed"); exit(1);
	}
	return 0;
}

void chat(void * shmaddr){
	int semid;
	char buf[128];

	sleep(1);

	if((semid = initsem(1)) < 0){
		exit(1);
	}

	strcpy(shmaddr, "---Chat Start---\n");

	while(1){
		semlock(semid);

		strcpy(buf, shmaddr);
		printf("Recv : %s\n",buf);
		printf(" > Message : ");
		fgets(buf,128, stdin);
		printf("Send : %s\n",buf);
		strcpy(shmaddr, buf);

		semunlock(semid);
	}
}

void handler(int dummy){;}


void server(){
        key_t key;
        int shmid;
        void *shmaddr;
        char buf[128];
        sigset_t mask;
	int isConnected = 0;

        key = ftok("shkey",1);
        shmid = shmget(key, 128, IPC_CREAT|0644);

        printf("------server-------\n");

        shmaddr = shmat(shmid, 0, 0);
	strcpy(shmaddr, "1. Chat\n2.DownloadFile");

	printf("Listner wait for Client\n");

	while(!isConnected){
		strcpy(buf, shmaddr);
		if(strcmp(buf,"1") == 0 || strcmp(buf,"2") == 0)
			isConnected = 1;

		printf("what : %s\n", buf);

	}

	if(strcmp(buf,"1") == 0){
		chat(shmaddr);
	}

	else if (strcmp(buf,"2") == 0){
		//download(shmaddr);
	}


        shmdt(shmaddr);
}





void client(){
	key_t key;
	int shmid;
	void *shmaddr;
	char buf[128];
		
	key = ftok("shkey",1);
	shmid = shmget(key, 128, IPC_CREAT|0644);
	
	printf("------Client-------\n");
	
	shmaddr = shmat(shmid, 0, 0);
	
	strcpy(buf, shmaddr);
	printf("Server Send\n%s\n",buf);

	printf("Answer : ");
	scanf("%s",buf);

	if(strcmp(buf,"1") == 0){
		chat(shmaddr);
	}
	
	else if (strcmp(buf,"2") == 0){
//		download(shmaddr);
	}
	
	
	shmdt(shmaddr);
}
