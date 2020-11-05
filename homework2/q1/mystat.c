#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	struct stat buf;
	int i;

	stat(argv[1], &buf);
	
	printf("Filename : %s\n", argv[1]);
	printf("Inode no. : %d\n", (int)buf.st_ino);
	printf("File type : ");

	if(S_ISFIFO(buf.st_mode)) printf("%s\n", "FIFO");
	if(S_ISCHR(buf.st_mode)) printf("%s\n", "text devices file");
	if(S_ISDIR(buf.st_mode)) printf("%s\n", "directory");
	if(S_ISBLK(buf.st_mode)) printf("%s\n", "block Device file");
	if(S_ISREG(buf.st_mode)) printf("%s\n", "regular File");
	if(S_ISLNK(buf.st_mode)) printf("%s\n", "simlink file");
	if(S_ISSOCK(buf.st_mode)) printf("%s\n", "socket file");

	printf("Permission : " );

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
	
	printf("Number of link = %o\n", (unsigned int) buf.st_nlink);
	printf("Size : %d\n", (int)buf.st_size);


	return 0;
}
