#include <stdio.h>

extern int add(int a, int b);
extern int sub(int a, int b);
extern int mul(int a, int b);

int main(int argc, char* argv[]){
	int i;
	int a,b;
	int res;

	printf("<Calculator Menu\n");	
	printf("1.Add\n2.Sub\n3.Mul\nEnter : ");
	
	scanf("%d",&i);

	if(i < 1 || i > 3){
		printf("Wrong input (Only 1~3)\n");
		return -1;
	}

	printf("Enter two numbers : ");
	scanf("%d %d", &a,&b);

	
	switch(i){
		case 1:
			res = add(a,b);
			printf("Result : %d + %d = %d\n", a,b,res);
			break;
		case 2:
			res = sub(a,b);	
			printf("Result : %d - %d = %d\n", a,b,res);
			break;
		case 3: 
			res = mul(a,b);
			printf("Result : %d * %d = %d\n", a,b,res);
			break;
	}
	
	return 0;
}
