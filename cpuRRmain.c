#include <stdio.h>


int main() {
	/* code */
	
	int bt[20],at[20],wt[20],tat[20],dup[20],awt = 0, atat = 0,q,i,j,k,n,temp,tbt = 0;

	printf("Enter no. of processes: " );

	scanf("%d",&n);

	printf("Enter time quantum: ");

	scanf("%d",&q );

	printf("\n\nBurst time of: \n" );

	for (i = 0; i < n; ++i) {
		/* code */
		printf("\t\tP[%d]: ",i+1);

		scanf("%d",&bt[i]);

		tbt += bt[i];

		dup[i] = i+1;

		wt[i] = 0;

	}

	while ( tbt > 0 ) {

		for(i = 0; i < n; i++) {

			if(bt[i] > q) {

				bt[i] -= q;

				tat[i] += q;

				tbt -= q;

				for( j = 0; j < n; j++) {

					if(bt[j] != 0 && i != j) {

						wt[j] += q;

					}

				}

			}

			else if (bt[i] > 0) {

				tbt -= bt[i];

				tat[i] += bt[i];

				for( j = 0; j < n; j++) {

					if(bt[j] != 0 && i != j) {

						wt[j] += bt[i];

					}

				}

				bt[i] = 0;

			}

		}

	}
	printf(" Process\tWaiting Time\tTurnAround Time \n");
	for (int i = 0; i < n; ++i) {
		
		printf("   %d\t\t\t%d\t\t%d\n",dup[i],wt[i],tat[i]);

		awt += wt[i];

		atat += tat[i] + wt[i];

	}
	printf("Average Waiting Time = %.2f\n", (float)awt/n);

	printf("Average TurnAround Time = %.2f\n",(float)atat/n);

}	