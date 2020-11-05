#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printPermission(struct stat buf){
	int i;
	for(i = 0; i < 3 ; i++)
	{
		if(((buf.st_mode << 3*i) & S_IRUSR) != 0) printf("r"); 
		else printf("-");
		if(((buf.st_mode << 3*i) & S_IWUSR) != 0) printf("w");
		else printf("-");
		if(((buf.st_mode << 3*i) & S_IXUSR) != 0) printf("x");
		else printf("-");
	}
	printf("\n");
}


int main(int argc, char *argv[]){
	struct stat buf;
	unsigned int per = 0;

	if(argc == 2){
		stat(argv[1],&buf);
		printf("Permission : ");
		printPermission(buf);
	}
	else if (argc == 3){
		stat(argv[2],&buf);
		printf("Permission (before) : ");
		printPermission(buf);


		if(argv[1][0] == '+'){
		// mychmod +x test
			if (strchr(argv[1] ,'r')  != NULL)
				per = per | S_IREAD | S_IRGRP | S_IROTH;
			
			if (strchr(argv[1],'w') != NULL)
				per = per | S_IWRITE | S_IWGRP | S_IWOTH;
			
			if (strchr(argv[1],'x') != NULL)
				per = per | S_IXUSR | S_IXGRP | S_IXOTH;

			chmod(argv[2],buf.st_mode | per);
			
		}
		
		else if (argv[1][0] == '-'){
		// mychmod -x test
			per = buf.st_mode;
			if (strchr(argv[1],'r') != NULL)
				per &= ~(S_IREAD | S_IRGRP | S_IROTH);
			
			if (strchr(argv[1],'w') != NULL)
				per &= ~(S_IWRITE | S_IWGRP | S_IWOTH);
		
			if (strchr(argv[1],'x') != NULL)
				per &= ~(S_IXUSR | S_IXGRP | S_IXOTH);
			
			chmod(argv[2], per);
			
		}
		else {
		// mychmod 777 test
			sscanf(argv[1] , "%o", &per);
			chmod(argv[2], per );
		}

		stat(argv[2],&buf);
		printf("Permission (after) : ");
		printPermission(buf);
	}

	return 0;
}


