#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



pthread_mutex_t mutex;

struct account{
	int balance;
	int saving;
};

int withdraw(struct account *account, int amount);
void disburse_money(struct account *account, int amount);
void *with1(void *account);
void *with2(void *account);


int main(void){
	pthread_t t1, t2;
	struct account a = {500,500};

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t1, NULL, with1, (void *)&a);
	pthread_create(&t2, NULL, with2, (void *)&a);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}




void *with1(void *account){
	withdraw((struct account *)account,300);
	return 0;
}

void *with2(void *account){
	withdraw((struct account *)account,400);
	return 0;
}


int withdraw(struct account *account, int amount){
	pthread_t id = pthread_self();
//	const int balance = account->balance;

	pthread_mutex_lock(&mutex);

	if(account->balance < amount){
		printf("-[balance] : You don't have Money \n");
		return -1;
	}

	sleep(1);
	account->balance = account->balance - amount;

	printf("ID:%d..[before disburse] balance : %d , saving : %d\n" ,(int)id, account->balance, account->saving);

	disburse_money(account, amount);

	pthread_mutex_unlock(&mutex);
	printf("ID:%d..[after disburse] balance : %d , saving : %d\n" ,(int)id, account->balance, account->saving);


	return 0;
}


void disburse_money(struct account *account, int amount){
	int res;

	//res = account->saving;
	if(account->saving < 0){
		printf("-[saving] :  you don't have money\n");
		return;
	}

	sleep(1);
	account->saving = account->saving - amount;
	printf("---chulgum Success---\n");
	return;
}
