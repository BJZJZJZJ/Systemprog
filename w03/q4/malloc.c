#include <stdio.h>
#include <stdlib.h>


int main(){
	int size = 10;
	int n = 0;
	int* arr;
	int sum = 0;

	int i = 0; // loop index

	printf("initial value\n");
	printf("size : %d , n = %d, sum = %d\n",size, n, sum);

	printf("----------\nAscending Loop\n\n");

	arr = (int*) malloc(sizeof(int) * size);

	for ( i = 0 ; i < 100 ; i++){
		*(arr + i) = i+1;	
		n++;
		sum = sum + (i+1);

		if(size <= n){
#ifdef DEBUG
			printf("Before : %d\n",size);
#endif
			size = size * 2;
			arr = (int*) realloc(arr, sizeof(int) * size);
#ifdef DEBUG
			printf("after : %d\n", size);
#endif
		}
	}
	printf("** result : size : %d , n = %d, sum = %d\n",size, n, sum);


	printf("----------\nDecending Loop\n\n");

	for ( i = 100 ; i > 10 ; i--){
		*(arr+(i-1)) = -1;
		n--;
		sum = sum - i;

		if ( n <= size / 4 ){
#ifdef DEBUG
			printf("Before : %d\n" ,size);
#endif
			size = size / 2;
			arr = (int*) realloc(arr, sizeof(int) * size);
#ifdef DEBUG
			printf("After : %d\n" , size);
#endif
		}
	}
	printf("** result : size : %d , n = %d, sum = %d\n",size, n, sum);

	free(arr);

	return 0;
}
