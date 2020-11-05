#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(void){
	struct servent *port;
	char s[20];
	int n;

	printf("Enter the Service Name  : ");
	scanf("%s",s);

	setservent(0);

	for (n = 0 ; n < 1000 ; n++){
		port = getservent();
		if(strcmp(port->s_name,s) != 0)
			continue;
		else if (strcmp(port->s_name,s) == 0)
			break;
	}

	printf("Well-Known-Port Number : %d\n",htons(port->s_port));

	endservent();

	return 0;
}
