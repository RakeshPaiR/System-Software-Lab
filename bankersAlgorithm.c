#include<stdio.h>

int flag[20],m;

int isUnSafe(int need[][5], int finish[],int work[],int n) {

	int j,i;

	for ( i = 0; i < n; ++i)
	{
		for ( j = 0; j < m; ++j)
		{
			if(need[i][j] > work[j]) {

				flag[i] = 0;

				break;

			}
			if(j==m-1) {

				flag[i] = 1;

			}
		}

		if(flag[i] && finish[i] == 0) {

			return 0;

		}
	}
	return 1;

}

int main(int argc, char const *argv[])
{
	int maximum[20][5],finish[20],allocation[20][5],available[5],need[20][5],i,j,tneed=0,n,work[5],k;

	printf("Enter no. of processes: "); scanf("%d",&n);

	printf("Enter no. of resources: "); scanf("%d",&m);

	for ( i = 0; i < n; ++i)
	{

		for ( j = 0; j < m; ++j)
		{

			printf("maximum[%d][%c]: ",i,j+'A');scanf("%d",&maximum[i][j]);

			printf("allocation[%d][%c]: ",i,j+'A'); scanf("%d",&allocation[i][j]);

			need[i][j] = maximum[i][j] - allocation[i][j];

			tneed += need[i][j];

			printf("%d\n",tneed);
			
		}

		flag[i] = 0;
		
		finish[i] = 0;

		

	}
	for ( j = 0; j < m; ++j) {printf("Enter available[%c] ",j+'A');scanf("%d",&available[j]);}

	for ( j = 0; j < m; ++j) work[j] = available[j];

	for ( i = 0; i < n; ++i)
	{

		for ( j = 0; j < m; ++j)
		{
			if(need[i][j] > work[j]) {

				flag[i] = 0;

				break;

			}
			if(j == m-1) {

				flag[i] = 1;

			}
		}


		if (finish[i] == 0 && flag[i])
		{
			work[j] =  work[j] + allocation[i][j];

			finish[i] = 1;

			for ( j = 0; j < m; ++j)
			{
				tneed -= need[i][j];

				need[i][j] = 0;
			}

			

			printf("P[%d] ",i);
		}
	
		
		if(tneed == 0) {

			break;

		}
		else if (isUnSafe(need,finish,work,n))
		{
			printf("\n Unsafe State!! Deadlock may occur!!!");

			break;
		}
		else {

			if(i == n-1) i = -1;

		}
	}

	printf("bankers Completed");
	return 0;
}
