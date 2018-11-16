#include<stdio.h>
#include <string.h>
int main(){
	char bin[][5] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char hexs[][4] = {"0000","0001","1111"}, objCode[5];
	int i, j;
	for (i = 0; i < 5; i++) {
		// printf("%s", hexes[i]);
		// printf("%s ", hexs[i]);
		for(j = 0; j< 16; j++) {
			printf("%s %s \n", hexs[i],bin[j]);
			if(!strcmp(hexs[i],bin[j])) {
				// printf("%s\n", "TRUE");
				objCode[i] = hex[j];
				printf("%s",objCode);
				break;
			}
		}
	}
}
