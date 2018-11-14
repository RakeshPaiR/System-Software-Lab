#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directory {
	char dname[25];
	char fname[10][25];
	int file_count;
}dir[10];

int findDir(char fold[25],int dc) {
	int i;
	for(i = 0; i < dc; i++) {
		if(!strcmp(fold,dir[i].dname)) {
			return i;
		}
	}
	if(i == dc) {return -1;}
}

int main(int argc, char const *argv[]) {
	int i, n, t, dir_count = 0,j;
	char file[25],mainDirectory[25];
	printf("Enter directory name: ");
	scanf("%s",mainDirectory);

	do {

		printf("\n\n1.Create Directory\n2.Search Directory\n3.Delete Directory\n4.Create file\n5.Search File\n6.List Files\n7.Delete File\nEnter your choice: (Enter\"0\" to exit)\n");
		scanf("%d",&t);

		switch(t) {

			case 1: printf("\nEnter name of directory to be created: ");
					scanf("%s",dir[dir_count ++].dname);
					dir[dir_count-1].file_count = 0;
					printf("\n\tDirectory \"%s\" created at index %d",dir[dir_count-1].dname,dir_count-1);
					break;

			case 2: printf("\nEnter directory to be searched: ");
					scanf("%s",file);
					if(strcmp("",file)) {
						n = findDir(file,dir_count);
						if(n == -1) {
							printf("\n\tDirectory \"%s\" not found",file);
						}
						else {
							printf("\n\tDirectory \"%s\" found at index %d", file, n);
						}
					}
					break;

			case 3: printf("Enter directory to be deleted: ");
					scanf("%s",file);

					for (i = 0; i < dir_count; ++i) {
						if(!strcmp(file,dir[i].dname)) {
							strcpy(dir[i].dname,"");
							dir[i].file_count = 0;
							printf("\n\tDirectory \"%s\" deleted.",file);
							break;
						}
					}
					if (i == dir_count) {
						printf("\n\tDirectory \"%s\" not found.",file);
					}
					break;
			
			case 4: printf("\nEnter directory in which file is to be created: ");
					scanf("%s",file);
					if(strcmp("",file)) {
						n = findDir(file, dir_count);
						if(n != -1) {	
							printf("\nEnter file name: ");
							scanf("%s",dir[n].fname[dir[n].file_count ++]);
							printf("\n\tFile created at: %s -> %s",dir[n].dname,dir[n].fname[dir[n]. file_count - 1] );
						}
						if(n == -1) {
							printf("\n\tDirectory \"%s\" not found.",file);
						}
					}
					break;
			case 5: printf("\nEnter file to be searched: ");
					scanf("%s",file);
					n = 0;
					if(strcmp("",file)) {
						for(i = 0; i < dir_count; i++ ) {
							for(j = 0; j < dir[i].file_count; j++) {
								if(!strcmp(dir[i].fname[j],file)){
									printf("\n\tFile found at: %s -> %s",dir[i].dname,dir[i].fname[j]);
									n = 1;
									break;
								}
							}
							if(n) {
								break;
							}
						}
						if( i == dir_count) {
							printf("\n\tFile \"%s\" not found",file );
						}
					}
					break;

			case 6: if (dir_count == 0) {
						printf("\n\tNothing to display!!!");

					}
					else {
						printf("\n\t%s -> ",mainDirectory);
						for ( i = 0; i < dir_count; ++i) {
							if(strcmp("",dir[i].dname)) {
								printf("\n\t\t%s -> ",dir[i].dname);
								for(j = 0; j < dir[i].file_count; j++) {
									printf("\n\t\t\t%s", dir[i].fname[j]);
								}
							}
						}
					}
					break;

			case 7: printf("\nEnter file to be deleted: ");
					scanf("%s",file);
					n = 0;
					for ( i = 0; i < dir_count; ++i) {
						for(j = 0; j < dir[i].file_count; j++) {
							if(!strcmp(file,dir[i].fname[j])) {
								strcpy(dir[i].fname[j],"");
								n = 1;
								printf("File \"%s\" in Directory \"%s\" deleted.",file, dir[i].dname);
								break;
							}
						}
						if(n) {
							break;
						}
						if(i == dir_count) {
							printf("\n\tFile \"%s\" not found.",file);
						}
					}
					break;

			//if(dir[0].file_count == 0) {
			// 			printf("\n\tNo files to be displayed");
			// 		}
			// 		else {
			// 			printf("\t%s ->",dir[0].dname);
			// 			for (i = 0; i < dir[0].file_count; ++i) {	
			// 				if(strcmp(dir[0].fname[i],""))
			// 					printf("\n\t\t%s",dir[0].fname[i]);
			// 			}
			// 		}
			// 		break;

			// case 4: printf("\nEnter file to be deleted: ");
			// 		scanf("%s",file);

			// 		for (i = 0; i < dir[0].file_count; ++i) {	
			// 			if(!strcmp(file,dir[0].fname[i])) {
			// 				strcpy(dir[0].fname[i],"");
			// 				printf("\n\tFile \"%s\" deleted.",file);
			// 				break;
			// 			}
			// 		}
			// 		if (i == dir[0].file_count) {
			// 			printf("\n\tFile \"%s\" not found", file);
			// 		}
			// 		break;

			case 0: exit(0);

			default: printf("Enter a number as per instruction, Try Again!!\n");

		}

	} while (t != 0);

	return 0;
}