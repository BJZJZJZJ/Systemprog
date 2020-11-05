#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <limits.h>
#include <time.h>

void func_O1(int a);
void func_ON(int a);
void func_ON2(int a);
void func_ON3(int a);

int main(){
	int a = 3000; // (100,000,000)
	clock_t t1,t2;
	struct tms mytms;

	t1 = clock();
	func_O1(a);
	t2 = clock();
	printf("func_O1 takes %.3f seconds.\n" , (double)(t2-t1)/CLOCKS_PER_SEC);

	t1 = clock();
	func_ON(a);
	t2 = clock();
	printf("func_ON takes %.3f seconds.\n" , (double)(t2-t1)/CLOCKS_PER_SEC );

	t1 = clock();
	func_ON2(a);
	t2 = clock();
	printf("func_ON2 takes %.3f seconds.\n" , (double)(t2-t1)/CLOCKS_PER_SEC);

	/* func_ON3 call */

	t1 = clock();
	func_ON3(a);
	t2 = clock();
	printf("func_ON3 takes %.3f seconds.\n" , (double)(t2-t1)/CLOCKS_PER_SEC);
	return 0;
}

void func_O1(int a){
	a++;
}

void func_ON(int a){
	int i,j;
	for (i=0 ; i<a ; i++)
		j++;	
}

void func_ON2(int a){
	int i,j,k;
	for (i=0 ; i<a ; i++)
		for (j=0 ; j<a ; j++)
			k++;
}

void func_ON3(int a){
	int i,j,k,l;
	for (i=0 ; i<a ; i++)
		for (j=0 ; j<a ; j++)
			for (k=0; k<a ; k++)
				l++;
}

