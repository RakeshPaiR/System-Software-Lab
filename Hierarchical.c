#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct directory {
	char dname[25];
	struct directory *subdir[8];
	struct directory *parent;
	char fname[10][25];
	int f_count,active,counter;// active is directory count
} dir,*temp;

struct directory *find_dir(char name[25], struct directory *root) {

	int i,flag;
	struct directory *temp;
	if(!strcmp(name,root -> dname)) {
		return root;
	} else {
		for  (i = 0; i < root -> active; ++i)
		{
			temp = find_dir(name, root->subdir[i]);
			if(temp != NULL) {
				return temp;
			}
		}
	}
	return NULL;
	
}

int display_all(struct directory *root) {

	int i, j,flag;
	int temp;
	printf("\n\t+%s -> +%s\n", (root -> parent)->dname,root -> dname);
	for( j = 0; j < root -> f_count; j++) {
			printf("\n\t\t-%s",root->fname[j]);
	}
	for  (i = 0; i < root -> active; ++i)
	{	
		temp = display_all(root->subdir[i]);
		if(temp != 0) {
			return 1;
		}
	}
	return 0;
}

struct directory *create_dir(char name[25], struct directory *root) {

	struct directory *newnode = malloc(sizeof(struct directory));
	strcpy(newnode -> dname,name);
	newnode -> f_count = 0;
	newnode -> active = 0;
	newnode -> counter = 0;
	newnode -> parent = root;
	for (int i = 0; i < 8; ++i){
		
		newnode -> subdir[i] = NULL;
	}
	return newnode;
}

void delete_dir(struct directory *root, char name[25]) {

	int i = 0;
	for (i = 0; i < root->active; ++i) {
		if(!strcmp(name,(root->subdir[i])->dname)) {
			temp = root->subdir[i];
			break;
		}
	}
	for(; i < (root->active) -1; i++) {

		(root -> subdir[i]) = (root ->subdir[i+1]);
	}
	for (i = 0; i < temp->active; ++i){
		
		free(temp->subdir[i]);
	}
	free(temp);
	root -> active --;

}
int find_file(struct directory *root, char name[25]) {
	int i = 0;
	for(i = 0; i < root->f_count; i++) {

		if(!strcmp(root->fname[i],name)) {

			return 1;
		}
	}
	for(i = 0 ; i < root -> active ; i++ ) {

		return find_file(root -> subdir[i], name);
	}
	return 0;

}

int main(int argc, char const *argv[]){

	int i, n, t, j;
	char name[25], tempname[25];
	printf("Enter name of Directory: ");
	scanf("%s",dir.dname);
	dir.f_count = 0;
	dir.active = 0;
	dir.parent = NULL;
	dir.counter = 0;
	for (int i = 0; i < 8; ++i)
	{
		dir.subdir[i] = NULL;
	}
	do {

		printf("\n\n1.Create Directory\n2.Search Directory\n3.Delete Directory\n4.Create file\n5.Search File\n6.List Files\n7.Delete File\nEnter your choice: (Enter\"0\" to exit)\n");
		scanf("%d",&t);

		switch(t) {

			case 1: printf("Enter directory in which directory is to be created: ");
					scanf("%s",tempname);
					temp = find_dir(tempname,&dir);
					if(temp != NULL) {
						printf("Enter directory name to be created: ");
						scanf("%s",name);
						temp->subdir[(temp->active)++] = create_dir(name,temp);
						printf("\n\tDirectory \"%s\" created inside \"%s\"",temp->subdir[temp->active-1]->dname,temp->dname);
					}
					else {
						printf("\n\tDirectory \"%s\" not found",tempname);
					}
					break;

			case 2: printf("Enter directory to be Searched: ");
					scanf("%s",name);
					temp = find_dir(name,&dir);
					if(temp != NULL) {
						printf("\n\tDirectory found!!!");
					} else {
						printf("\n\tDirectory \"%s\" not found",name);
					}
					break;

			case 3: printf("Enter name of directory to be deleted: ");
					scanf("%s",name);
					if(strcmp(dir.dname,name)){
						temp = find_dir(name,&dir);
						if(temp != NULL) {
							
							delete_dir(temp->parent, name);
							printf("\n\tDirectory \"%s\" deleted.",name);
						} else {

							printf("Directory \"%s\" not found",name);
						}
					} else {
						printf("\n\tROOT directory can't be deleted.");
					}
					break;

			case 4: printf("Enter directory in which file is to be created: ");
					scanf("%s",tempname);
					temp = find_dir(tempname,&dir);
					if(temp != NULL) {
						printf("Enter name of file to be created: ");
						scanf("%s",name);
						strcpy(temp->fname[temp->f_count++],name);
						printf("\n\tFile \"%s\" created in directory \"%s\".",name,tempname);
					} else {
						printf("\n\tDirectory \"%s\" not found",tempname);
					}
					break;

			case 5: printf("\nEnter file name to be searched:");
					scanf("%s",name);
					if(find_file(&dir,name)) {
						printf("File \"%s\" found.",name);
					} else {

						printf("File \"%s\" not found.",name);
					}
					break;

			case 6: display_all(&dir);
					break;

			case 7: printf("Enter file to be deleted: ");
					scanf("%s",name);
					printf("Enter directory in which file is located: ");
					scanf("%s",tempname);
					n = 1;
					temp = find_dir(tempname,&dir);
					if(temp != NULL) {
						printf("%s\n", temp  ->dname);
						for(i = 0; i < temp -> f_count; i++) {
							if(!(strcmp(name,temp -> fname[i]))) {
								for(j = i; j < temp -> f_count -1; j++) {
									strcpy(temp -> fname[j],temp -> fname[j + 1]);
								}
								strcpy(temp -> fname[temp -> f_count --],"");
								printf("\n\tFile \"%s\" is deleted", name);
								n = 0;
								break;
							}
						} 
						if(n) {
							printf("\n\tFile \"%s\" not found!!!", name);
						}
					}
					else {
						printf("\n\tDirectory \"%s\" not found",tempname);
					}
					break;


			case 0: exit(0);

			default: printf("\n\tEnter a number as per instruction, Try Again!!\n");

		}

	} while (t != 0);

	return 0;
}