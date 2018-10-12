// This program is intended to find the seek time occured using fcfs disk scheduling algorithm,
#include<stdio.h>

#include<math.h>

int main(int argc, char const *argv[]) {

	int n,sh,loc[20],thm = 0,i;

	printf("Enter size of queue: ");
	scanf("%d",&n);

	printf("Enter initial head position: ");
	scanf("%d",&sh);

	printf("Enter queue elements: ");
	for (int i = 0; i < n; ++i) {
		
		scanf("%d",&loc[i]);
	}
	
	printf("\nDisk access Sequence is: ");
	printf(" %d  ", sh);

	for (int i = 0; i < n; ++i) {

		thm += abs(sh - loc[i]);
		sh = loc[i];
	}

	for (i = 0; i < n-1; ++i) {
	
		printf(" %d  ", loc[i]);
	}

	printf(" %d", loc[i]);
	printf("\nTotal Seek time is: %d", thm);
	printf("\nAverage Seek time is: %.2f\n", (float)thm/n);

	return 0;
}
