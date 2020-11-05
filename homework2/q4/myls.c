#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *dent;

	int i=0; int j=0; int k=0; // file counter
	int l; // loop index

	// file name array
	char reg[20][15];
	char dir[20][15];
	char other[20][15];

	if((dp = opendir(".")) == NULL){
		printf("Directory Open Fail\n");
		exit(1);
	}

	// read Directory
	while((dent = readdir(dp))){
		if(dent->d_type == DT_REG){
			sscanf(dent->d_name, "%s", reg[i]);
			i++;
		}
		else if(dent->d_type == DT_DIR){
			if(dent->d_name[0] == '.')
				continue;

			sscanf(dent->d_name, "%s", dir[j]);
			j++;
		}
		else {
			sscanf(dent->d_name, "%s",other[k]);
			k++;
		}		
	}

	// Output File name
	printf("<Regular Files>\n");
	for (l = 0 ; l < i ; l++)
		printf("%s\n",reg[l]);
	
	printf("\n<Directories>\n");
	for (l = 0 ; l < j ; l++)
		printf("%s\n", dir[l]);
		
	printf("\n<Others>\n");
	for(l = 0 ; l < k ; l++)
		printf("%s\n", other[l]);

	return 0;
}


