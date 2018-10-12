#include<stdio.h>

#include<math.h>

void sort(int a[], int n)
{
    int i, j, min, temp;
    for (i=0; i<n; i++)
    {
        min = i;
        for (j=i+1; j<n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

int main(int argc, char const *argv[]) {

	int n,thm = 0,l = 0,sh,locg[20],locl[20],u ,d, g = 0,val,i;

	printf("Enter size of queue: ");

	scanf("%d",&n);

	printf("Enter initial head position: ");

	scanf("%d",&sh);

	printf("Enter lower and upper disk limit: ");

	scanf("%d %d",&d,&u);

	printf("Enter queue elements: ");

	for (int i = 0; i < n; ++i) {
		
		scanf("%d",&val);

		if(val > u || val < d) {

			printf("Value out of disk range!!! Re-Enter another value");

			i--;

		}
		else if(val > sh) {

			locg[g++] = val;
			
		}
		else {

			locl[l++] = val;

		}

	}

	sort(locg,g);

	sort(locl,l);

	if (sh < (l+u)/2) {

		printf("\nDisk seek sequence is: ");

		printf("%d --> ", sh);				

		for(i = l-1; i > -1; i--) {

			thm += abs(sh - locl[i]);

			sh = locl[i];

			printf("%d --> ", sh);

		}

		thm += abs(sh - d);

		sh = d;

		printf("%d --> ", sh);	

		sh = u;

		printf("%d -->", sh);	//assuming moving to end won't take any time and occur immediately.

		for (int i = g-1; i > 0; --i) {
			
			thm += abs(sh - locg[i]);

			sh = locg[i];

			printf("%d --> ", sh);			

		}
		thm += abs(sh - locg[0]);

		printf("%d\n", locg[0]);


	} else {

		printf("Disk seek sequence is: ");

		printf("%d --> ", sh);		

		for (int i = 0; i < g; ++i) {
			
			thm += abs(sh - locg[i]);

			sh = locg[i];

			printf("%d --> ", sh);			

		}
		thm += abs(sh - u);

		sh = u;

		printf("%d --> ", sh);

		sh = d;

		printf("%d --> ", sh);	//assuming moving to end won't take any time and occur immediately.

		for(i = 0; i < l-1; ++i) {

			thm += abs(sh - locl[i]);

			sh = locl[i];

			printf("%d --> ", sh);

		}
		thm += abs(sh - locl[l-1]);

		printf("%d\n", locl[l-1]);

	}

	printf("Total Seek Time: %d\n", thm);

	printf("Average Seek Time: %.3f\n",(float)thm/n);
	
	printf("Disk Scan is completed");

}
