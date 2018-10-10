#include<stdio.h>
#include <string.h>
#include <stdlib.h>

struct files {
	
	char fileName[25];

	struct files *file;

};
struct directory {

		char dirName[25];

		struct files *file;

};

struct directory *MKDIR(char name[]) {

	struct directory *newDir = malloc(sizeof(struct directory));

	strcpy(newDir -> dirName, name);

}

void main() {

	struct directory *home = NULL;

	char cmd[10],dirname[25];

	printf("\t\t\t**********************Help File***********************\n");

	printf("Use usual linux commands to create, delete, change directory.\n");
	printf("Create directory: />$ mkdir [directory_name]\n");
	printf("Delete directory: />$ rmdir [directory_name]\n");
	//printf("Change directory: />$ cd [directory_name]\n");
	//printf("Present Working directory: />$ pwd\n");

	printf("Use familiar linux commands to create, delete file\n");

	printf("Create file: />$ cat > [file_name]\n");
	printf("Delete file: />$ rm [file_name]\n");
	printf("Search file: />$ find [file_name]\n");
	printf("Display all files: />$ ls\n");

	printf("Quit using \"quit\" command");

	printf("Enter your commands below");

	printf("-------N.B : Create directory before creating files--------");

	printf("\t\t\t******************************************************\n");

	printf("/>$ ");

	scanf("%s %s",cmd,dirname);

	if(!strcmp(cmd,"cd")) {

		home = MKDIR(dirname);

		printf("Now you can create files using \"cat > [file_name]\"");

		do {

			printf("%s/>$ ", dirname);

		} while(cmd != "quit");

	} else {

		printf("Create directory first!!! Use format as: cd [directory_name]\n");

	}

}