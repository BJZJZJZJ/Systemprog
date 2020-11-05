#include <stdio.h>
#include <netdb.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void){
	struct hostent *hent;
	char host[30];

	printf("Enter the Host Name : ");
	scanf("%s",host);

	sethostent(0);

	while((hent = gethostent()) != NULL){
		if(strcmp(hent->h_name,host) == 0)
			break;
		else 
			continue;
	}

	if(hent != NULL)
		printf("Host IP : %s\n", 
			inet_ntoa(*(struct in_addr*)hent->h_addr_list[0]));
	else 
		printf("404 Not Found\n");

	endhostent();


	return 0;
}
