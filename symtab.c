#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  HASH value%size

struct attr{
	int symval;
	char symname[20];
	struct attr *next;
};

void search(struct attr hash[],int size){
	int value ,flag = 0;
	printf("Enter the value of symbol:\n");
	scanf("%d",&value);
	struct attr *ptr;
	if(hash[HASH].symval == value){
		printf("FOUND, SYMBOL is %s\n",hash[HASH].symname);
		flag = 1;
	}
	else if(hash[HASH].next!=NULL)
	{
		ptr = hash[HASH].next;
		while(ptr!=NULL)
		{
			if(ptr->symval == value)
			{
				printf("FOUND, SYMBOL is %s\n",ptr->symname);
			}
			else
				ptr = ptr->next;
		}
	}
	if(!flag)
		printf("Not Found\n");
}

void insert(struct attr hash[],int size){

	int value;
	char name[20];

	printf("Enter the symbol name ");
	scanf("%s",name);
	
	printf("Enter the value ");
	scanf("%d",&value);

	if(hash[HASH].symval == 0){
		hash[HASH].symval = value;
		strcpy(hash[HASH].symname,name);
	}
	else{
		struct attr *chain;
		chain = (struct attr *)malloc(sizeof(struct attr *));
		chain->symval = value;
		strcpy(chain->symname,name);
		if(hash[HASH].next == NULL)
			chain->next = NULL;
		else
			chain->next = hash[HASH].next;
		hash[HASH].next = chain;

	}
}

void display(struct attr hash[],int size){
	int i;
	printf("\nSymbols \tValues\n");
	for(i = 0; i < size; i++){
		printf("%s \t %d",hash[i].symname,hash[i].symval);
		struct attr *ptr;
		if(hash[i].next!=NULL){
			ptr = hash[i].next;
			while(ptr != NULL){
				printf("  --->  %s - %d",ptr->symname,ptr->symval);
				ptr = ptr->next;
			}
		}
		printf("\n");
	}
}

void main(){

	int size,i,ch;
	printf("\nEnter the size of the table:\n\n");
	scanf("%d",&size);
	struct attr symbtab[size];
	for(i=0;i<size;i++){
		symbtab[i].next = NULL;
		symbtab[i].symval = 0;
		strcpy(symbtab[i].symname,"*");
	}

	do{

		printf("\nMENU\n\n1.INSERT\n2.SEARCH\n3.DISPLAY\n4.EXIT\n\n");
		printf("Enter Choice: ");
		scanf("%d",&ch);

		switch(ch){
			case 1: insert(symbtab,size);
					break;
			case 2: search(symbtab,size);
					break;
			case 3: display(symbtab,size);
					break;
			case 4: printf("EXIT\n");
		 	FILE *fp;
		 	fp = fopen("SYMBTAB.txt", "w");
	                for (i = 0; i < size; i++){
	                    fprintf(fp, "%s \t %d",symbtab[i].symname, symbtab[i].symval);
	                    struct attr *ptr;
	                    if(symbtab[i].next!=NULL){
	                        ptr = symbtab[i].next;
	                        while(ptr != NULL){
	                            fprintf(fp, " --> %s  %d", ptr->symname, ptr->symval);
	                            ptr = ptr->next;
	                        }
	                    }
	                    fprintf(fp, "\n");
	                }
	                fclose(fp);
					break;
			default: printf("INVALID CHOICE\n");
					break;
		}

	}while(ch!=4);
}