#include <netdb.h>
#include <stdio.h>

int main(void){
	struct servent *port;
	int p;
	int n;

	printf("Enter the Port number : ");
	scanf("%d",&p);

	setservent(0);

	for (n = 0 ; n < 1000 ; n++){
		port = getservent();
		if(p != htons(port->s_port))
			continue;
		else if (p == htons(port->s_port))
			break;
	}

	printf("Well-Known-Port Name : %s\n",port->s_name);

	endservent();

	return 0;
}
