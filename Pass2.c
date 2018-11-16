#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *lenFile , *optab, *symtab, *interFile, *record;
int LOCCTR;
char opcodes[30][20], objBinCode[32],objCode[9];

void bin2hex() {
	int i,j,t=0;
	char bin[][5] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char hexes[9][5],hexs[9][5];
	//printf("%s\n", objBinCode);
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 4 ; j++) {
			hexes[i][j] = objBinCode[t++];
		}
	}
	for (i = 0; i < 8; i++) {
		// printf("%s", hexes[i]);
		sprintf(hexs[i],"%.4s",hexes[i]);
		// printf("%s ", hexs[i]);
		for(j = 0; j< 16; j++) {
			//printf("%s %s \n", hexs[i],bin[j]);
			if(!strcmp(hexs[i],bin[j])) {
				// printf("%s\n", "TRUE");
				objCode[i] = hex[j];
				break;
			}
			//printf("%s\n",objCode);
		}
	}
	// for(i = 0; i < 5; i++) {
	// 	printf("%s ", hexs[i]);
	// }
	// printf("\n");
	// for(i = 0; i < 5; i++) {
	// 	//printf("%s ", hexs[i]);
		
	// }
}

void dec2bin(int c, char objBinCode[])
{
   int i , temp;
   printf("%d",strlen(objBinCode));
   for(i = strlen(objBinCode) - 1; i > -1; i--){
    	if((c & (1 << i)) != 0){
       		objBinCode[strlen(objBinCode) - 1 - i] = '1';
     	}else{
      		objBinCode[strlen(objBinCode) - 1 - i] = '0';
   		} 
   }
   for(i = 0; i < 8; i++) {
   		temp = objBinCode[i];
   		objBinCode[i] = objBinCode[strlen(objBinCode) - 8 + i];
   		objBinCode[strlen(objBinCode) - 8 + i] = temp;
   }
}

int hexToDec(char hexVal[]) {
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


int opFind(char opcode[]) {
	char str[100];
	int i;
	//printf("%s\n", opcode);
	fseek(optab,0,SEEK_SET);
	while(fgets(str,100,optab)!=NULL) {	
		i = splitWords(str,opcodes);
		if(!strcmp(opcodes[0],opcode)) {
			return hexToDec(opcodes[1]);
		}
	}
	// printf("%s%s", opcodes[0],opcode);
	return -1;
}

int objCodeGen(char line[]) {

	int dec,disp, n1, j, n = 0, i = 0, x = 0, b = 0, p = 0, e = 0;
	char words[5][20], dis[20];
	n1 = splitWords(line,words);
	// printf("%s\t", strtok(words[2],"+"));
	dec = opFind(strtok(words[2],"+"));
	// printf("%d\t",dec);
	dec2bin(dec,objBinCode);
	// printf("%s\n",objBinCode);
	if(dec != -1) {
		if(words[3][0] == '@') n = 1;
		if(words[3][0] == '#') {i = 1; b = 1; p = 0;}
		if(words[2][0] == '+') e = 1;
		if(words[3][0] != '@' && words[3][0] != '#') {
			n = 1;
			i = 1;
			b = 1;
			p = 0;
		}
		if(!(strcmp(words[2],"STL")) || !(strcmp(words[2],"J") || !(strcmp(words[2],"LDB")))) {
			p = 1;
			b = 0;
		}
		for(j = 0; j < strlen(words[3]); j++) {
			if(words[3][i] == ',') {
				x = 1;
			}
		}
		if(b) {
			disp = hexToDec(words[0]) - hexToDec("0033");
			if(disp < 0) {
				b = 0;
				p = 1;
			}
			else{
				dec2bin(disp,dis);
			}
			
		}
		if(p) {
			disp = hexToDec("FFFA") - hexToDec(words[0]);
			dec2bin(disp,dis);
		}
		printf("%s ", dis);
		// else {
		// 	disp = hexToDec(words[0]) - 
		// }
		objBinCode[6] = (n)?'1':'0';
		objBinCode[7] = (i)?'1':'0';
		objBinCode[8] = (x)?'1':'0';
		objBinCode[9] = (b)?'1':'0';
		objBinCode[10] = (p)?'1':'0';
		objBinCode[11] = (e)?'1':'0';
		bin2hex();
	}
	else strcpy(objCode,"");
	return b;
}


int main(int argc, char const *argv[]) {
	
	int i,j,l,n = 0 ,start,len;
	char str[80],line[50], length[10],first[10];
	char words[5][20], symbols[10][20];
	interFile = fopen("InterFile.txt","r");
	optab = fopen("OpTab.txt","r");
	symtab = fopen("SymTab.txt","r");
	record = fopen("ObjectCode.txt","w");
	lenFile = fopen("LengthFile.txt","r");

	if(interFile == NULL || optab == NULL || symtab == NULL || lenFile == NULL) {
		printf("File not found!!!");
		exit(0);
	}
	fgets(length,20,lenFile);
	fgets(line,50,interFile);
	n = splitWords(line,words);
	if(!strcmp("START",words[2])) {
		str[0]='H';
		strcat(str,"^");
		strcat(str,words[1]);
		strcat(str,"  ");
		strcat(str,"^");
		strcpy(first,words[0]);
		strcat(str,"00");
		strcat(str,words[0]);
		strcat(str,"^");
		strcat(str,"00");
		strcat(str,length);
		fprintf(record, "%s", str);
	}
	
	while(fgets(line,50,interFile)!=NULL) { 
		n = splitWords(line,words);
		if(!strcmp(words[2],"END")) {
			break;
		}
		if(strcmp(strtok(words[1],"\t"),"*")) {
			if(str[0]!='H' )
				fprintf(record, "\n%s", str);
				memset(str,0,sizeof(str));		
				str[0] = 'T';
				strcat(str,"^00");
				strcat(str,words[0]);
				//strcat(str,"^");
			
		}
		objCodeGen(line);
		//printf("%s",objCode);
		strcat(str,"^");
		strcat(str,objCode);

	}
	memset(str,0,sizeof(str));
	str[0] = 'E';
	strcat(str,"^00");
	strcat(str,first);
	fprintf(record, "\n%s", str);
	return 0;
}