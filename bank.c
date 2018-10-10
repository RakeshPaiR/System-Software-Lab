#include<stdio.h>

	int tneed = 0,finish[20];

	int deadlock(int a[20][5],int b[],int n, int m) {

		for (int i = 0; i < n; ++i)
		{
			int flag = 0;

			if(finish[i]) {

				continue;

			}

			for (int j = 0; j < m; ++j)
			{
				if (a[i][j] > b[j])
				{
					flag += 1;
				}
			}
			if(flag != 3) {

				return 0;

			}

		}
		return 1;

	}

	int mem_free(int a[],int b[],int m,int c[]) {

		for (int i = 0; i < m; ++i)
		{
			b[i] += a[i];

			tneed -= c[i];

			c[i] = 0;

		}

		return 1;

	}

	int arr_compare(int a[],int b[],int m) {

		for (int j = 0; j < m; ++j)
		{
			if( a[j] > b[j] ) {

				return 0;

			}
		}

		return 1;

	}

	int main(int argc, char const *argv[])
	{
		int maximum[20][5],allocation[20][5],available[5],need[20][5],i,j,n,work[5],k,m,flag[5],l=0,seq[20];

		char result[50] = {};

		printf("Enter no. of processes: "); scanf("%d",&n);

		printf("Enter no. of resources: "); scanf("%d",&m);

		printf("Enter Allocation Matrix:\n ");

		printf("  \t");

		for (i = 0; i < m; ++i){
			
			printf("%c\t", 'A' + i);
		
		}
		printf("\n");
		for( i = 0; i < n; i++) {

			printf("P[%d]\t",i + 1);

			for(j = 0; j < m; j++) {

				scanf("%d",&allocation[i][j]);

			}

		}

		printf("Enter Maximum Matrix:\n ");

		printf("  \t");

		for (i = 0; i < m; ++i){
			
			printf("%c\t", 'A' + i);
		
		}

		printf("\n");

		for( i = 0; i < n; i++) {

			printf("P[%d]\t",i + 1);

			for(j = 0; j < m; j++) {

				scanf("%d",&maximum[i][j]);

				need[i][j] = maximum[i][j] - allocation[i][j];

				tneed += need[i][j];

			}

			flag[i] = 0;

			finish[i] = 0;

		}

		printf("Enter Available resources: \n");

		for (int j = 0; j < m; ++j){
			
			printf("%c: \n",'A' + j);

			scanf("%d",&available[j]);

			work[j] = available[j];

		}

		for (int i = 0; i < n; ++i) {
			
			if(arr_compare(need[i],work,m) && !finish[i]) {

				if(finish[i] == 0) {

					if(mem_free(allocation[i],work,m,need[i])) {

						finish[i] = 1;

						seq[l++] = i;

					}

				}

			}

			if(deadlock(need,work,n,m)) {

				printf("Deadlock!!!");

				break;

			}
			else if(tneed > 0 && i == n-1) {

				i = -1;

			}

			if(tneed == 0) {

				printf("Safety sequence is: ");
				for (int i = 0; i < n; ++i)
				{
					printf("P[%d] ", seq[i]);
				}
				break;

			}

		}

	}