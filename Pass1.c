#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000


FILE *inFile , *optab, *symtab, *interFile, *lenFile;
int LOCCTR, sym;
char opcodes[30][20];

int hexToDec(char hexVal[]) 
{    
    int len = strlen(hexVal); 
    int base = 1; 
    int dec_val = 0; 
    for (int i=len-1; i>=0; i--) {    
        if (hexVal[i]>='0' && hexVal[i]<='9') { 
            dec_val += (hexVal[i] - 48)*base;               
            base = base * 16; 
        } 
        else if (hexVal[i]>='A' && hexVal[i]<='F') { 
            dec_val += (hexVal[i] - 55)*base; 
            base = base*16; 
        } 
    }
    return dec_val; 
}

int splitWords(char line[50],char words[][20]) {
	int i = 0,j = 0,k = 0;
	memset(words,0,sizeof(words[0][0])*5*20);
	j = 0;
	i = 0;
	if(line[0]=='\t') {
		strcpy(words[j++],"");
		i++;
		line[0] = '*';
		line[1] = '\t';
	}
	for (; i < strlen(line); ++i){
		if(line[i]=='\t'){
			while(line[i] == '\t' && i < strlen(line)) i++;
			k = 0;
			while(line[i] != '\t' && i < strlen(line) && line[i]!='\n') {
				words[j][k++] = line[i++];
			}
			j++;
		}
		else {
			k = 0;
			while(line[i] != '\t' && i < strlen(line) && line[i]!='\n') {
				words[j][k++] = line[i++];
			}
			j++;
		}
		if(line[i] == '\n' || line[i] == '\0') {
			return j;
		}
	}
	return j;
}
int search(char symtable[][20],char symbol[20]) {
	for (int i = 0; i < sym; ++i) {
		if(!strcmp(symbol,symtable[i])) {
			//printf("%s%s\n",symtable[i],symbol);
			return 1;
		}
	}
	return 0;
}
int opFind(char opcode[]) {
	char str[100];
	int i;
	//printf("%s\n", opcode);
	fseek(optab,0,SEEK_SET);
	while(fgets(str,100,optab)!=NULL) {	
		i = splitWords(str,opcodes);
		//printf("%s%s %d\n", opcodes[0],opcodes[1],i);
		if(!strcmp(opcodes[0],opcode)) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, char const *argv[]) {


	int i,j,l,n = 0 ,start;
	char str[25],line[50], hex[10];
	char words[5][20], symbols[10][20];
	char symtable[50][20];
	inFile = fopen("InFile.txt","r");
	optab = fopen("OpTab.txt","r");
	symtab = fopen("SymTab.txt","w+");
	interFile = fopen("InterFile.txt","w");
	lenFile = fopen("LengthFile.txt","w");
	if(inFile == NULL) {
		printf("InFile.txt is not found");
		exit(0);
	}
	if(interFile == NULL) {
		printf("InterFile.txt is not found");
		exit(0);
	}
	// while(fgets(line,SIZE,inFile) != NULL) {
	// 	printf("%s",line);
	// }
	// printf("\n");
	fgets(line,50,inFile);
	//printf("%s\n",line);
	n = splitWords(line,words);
	if(!strcmp(words[1],"START")) {
		LOCCTR = hexToDec(words[2]);

		fprintf(interFile, "%.4X\t%s\t\t\n",LOCCTR, strtok(line,"\n"));
	}
	else {
		LOCCTR = 0;
	}
	start = LOCCTR;
	while(fgets(line,50,inFile)!=NULL) {
		//printf("%s\n", line);
		n = splitWords(line,words);

		 //for (int i = 0; i < n; ++i) {
		 	//printf("%s\n", words[i]);
		 //}
		if(strcmp(words[0],"")) {
			//printf("%s", words[0]);
			if(search(symtable,words[0])) {
				printf("Error!!! Duplicate Symbol %s", str);
				return 0;
			}
			else {
				fprintf(symtab, "%s\t\t%.4X\n", words[0],LOCCTR);
				strcpy(symtable[sym++],words[0]);
			}
		}
		fprintf(interFile, "%.4X\t%s\t\t\n",LOCCTR, strtok(line,"\n"));
		if(opFind(words[1]) && strcmp(words[1],"END")) {
			//printf("%s\n", "TRUE");
			// printf("%.4X\t%s\n", LOCCTR,line);
			LOCCTR += 3;
			
		}
		else if(words[1][0] == '+') {
			if(opFind(strtok(words[1],"+"))) {
				// printf("%.4X\t%s\n", LOCCTR,line);
				LOCCTR += 4;
				
			}
		}
		else if(!strcmp(words[1],"WORD")) {
			// printf("%.4X\t%s\n", LOCCTR,line);
			LOCCTR += 3;
			
		}
		else if(!(strcmp(words[1],"RESW"))) {
			// printf("%.4X\t%s\n", LOCCTR,line);
			LOCCTR += (3*atoi(words[2]));
			
		}
		else if(!strcmp(words[1],"RESB")) {
			// printf("%.4X\t%s\n", LOCCTR,line);
			LOCCTR += atoi(words[2]);

		}
		else if(!strcmp(words[1],"BYTE")) {
			// printf("%.4X\t%s\n", LOCCTR,line);
			if(words[2][0] == 'X') {
				LOCCTR += 1;
			}
			else {
				LOCCTR += strlen(strtok(words[2],"C\'"));
			}
			
		}

		
	}
	printf("Program Length is: %d\n",(LOCCTR-start));
	fprintf(lenFile, "%.4X", (LOCCTR - start));

	exit(0);
	return 0;
}
