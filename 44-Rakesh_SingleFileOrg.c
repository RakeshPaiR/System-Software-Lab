#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directory {
	char dname[25];
	char fname[10][25];
	int file_count;

}dir;

int main(int argc, char const *argv[]) {
	int i, n, t;
	char file[25];
	dir.file_count = 0;
	printf("Enter directory name: ");
	scanf("%s",dir.dname);

	do {

		printf("\n\n1.Create file\n2.Search File\n3.List Files\n4.Delete File\nEnter your choice: (Enter\"0\" to exit)\n");
		scanf("%d",&t);

		switch(t) {

			case 1: printf("\nEnter name of file to be created: ");
					scanf("%s",dir.fname[dir.file_count++]);
					printf("\n\tFile \"%s\" created at index %d",dir.fname[dir.file_count-1],dir.file_count-1);
					break;

			case 2: printf("\nEnter file to be searched: ");
					scanf("%s",file);
					if(strcmp("",file)) {
						for (i = 0; i < dir.file_count; ++i) {
							if(!(strcmp(file,dir.fname[i]))) {
								printf("\tFile found at index %d", i);
								break;
							}
						}
						if(i == dir.file_count) {
							printf("\n\tFile \"%s\" not found",file );
						}
					}
					break;
			
			case 3: if(dir.file_count == 0) {
						printf("\n\tNo files to be displayed");
					}
					else {
						printf("\t%s ->",dir.dname);
						for (i = 0; i < dir.file_count; ++i) {	
							if(strcmp(dir.fname[i],""))
								printf("\n\t\t%s",dir.fname[i]);
						}
					}
					break;

			case 4: printf("\nEnter file to be deleted: ");
					scanf("%s",file);

					for (i = 0; i < dir.file_count; ++i) {	
						if(!strcmp(file,dir.fname[i])) {
							strcpy(dir.fname[i],"");
							printf("\n\tFile \"%s\" deleted.",file);
							break;
						}
					}
					if (i == dir.file_count) {
						printf("\n\tFile \"%s\" not found", file);
					}
					break;

			case 0: exit(0);

			default: printf("Enter a number as per instruction, Try Again!!\n");

		}

	} while (t != 0);

	return 0;
}