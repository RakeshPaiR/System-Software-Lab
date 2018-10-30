#include <stdio.h>
#include <string.h>


void main()
{

	int  t,k,size,s[10],s1[10][10],ch1,ch,flag=1;
	char dir[10],dir1[10][10],dir2[10][10][10],dir3[10][10][10][10],sea[10],d[10],d1[10];
	int i,j;

	printf("\nEnter the name of the parent db:");
	scanf("%s",dir);

	printf("\nEnter the number of directories:");
	scanf("%d",&size);

	for(i=0;i<size;i++)
	{
		printf("\nEnter the name of the directiory %d",i);
		scanf("%s",dir1[i]);
	}

//	printf("\nEnter the number of files in each directiory:");
	for(i=0;i<size;i++)
	{
		printf("\n Number of SUB-directiory  for directory %d : ",i+1);
		scanf("%d",&s[i]);

	}

	for(i=0;i<size;i++)
	{
		for(j=0;j<s[i];j++)
		{
			printf("Enter the SUB -directory %d in directory %d",i,j);
			scanf("%s",dir2[i][j]);
		}
	}

for(i=0;i<size;i++)
	{	for(j=0;j<s[i];j++)
		{ printf("\n For SUB-directiory %d : ",j+1);
	     	scanf("%d",&s1[i][j]);
	     }
	}

	for(i=0;i<size;i++)
	{
		for(j=0;j<s[i];j++)
		{
			for(k=0;k<s1[i][j];k++)
			{ printf("Enter the directory %d in sub-directory %d",k,j);
			  scanf("%s",dir3[i][j][k]);
		}
		}
	}




	printf("\nLevel : %s",dir);
	for(i=0;i<size;i++)
	{	printf("\nDirectory %d : %s",i,dir1[i]);
		for(j=0;j<s[i];j++)
		{
			printf("\nSub-Dired %d : %s",j,dir2[i][j]);
		
			for(k=0;k<s1[i][j];k++)
			{
				printf("\nFile name %d : %s",j,dir3[i][j][k]);		
			}
		}


	}

	


	do
	{	
		printf("\n1.Searching\n2.Adding\n3.Deleting\n4.Show:");
		scanf("%d",&ch1);

		switch(ch1)
		{

			case 1:
			flag=0;
			printf("\nENter the file to be searched:");
			scanf("%s",sea);
			for(i=0;i<size;i++)
	 {	//printf("\nDirectory %d : %s",i,dir1[i]);
		for(j=0;j<s[i];j++)
		{
			//printf("\nSub-Dired %d : %s",j,dir2[i][j]);
		
			for(k=0;k<s1[i][j];k++)
			{
					if(strcmp(sea,dir3[i][j][k])==0)
				{	printf("\nItem Found");
					flag=0;
					break;
				}					
			}
		}


	}
				
			if(flag)
			{
				printf("\nFile Not FOund");
			}
			break;

			case 2:
			printf("\nEnter the name to be added:");
			scanf("%s",sea);
			printf("\nEnter the directiory name to which file is to be enetrd:");
			scanf("%s",d);

			printf("Enter the sub-directory name to which file is to be entered:");
			scanf("%s",d1);
			
			for(i=0;i<size;i++)
			{
				if(strcmp(d,dir1[i])==0)

				{
					for(j=0;j<s[i];j++)
				{	if(strcmp(d1,dir2[i][j])==0)
					{
						for(k=0;k<s1[i][j];k++);

				  		strcpy(dir3[i][j][k],sea);
						s1[i][j]++;
						break;
					
				}
					break;	
				}
}
			
			}



	printf("\nLevel : %s",dir);
	for(i=0;i<size;i++)
	{	printf("\nDirectory %d : %s",i,dir1[i]);
		for(j=0;j<s[i];j++)
		{
			printf("\nSub-Dired %d : %s",j,dir2[i][j]);
		
			for(k=0;k<s1[i][j];k++)
			{
				printf("\nFile name %d : %s",j,dir3[i][j][k]);		
			}
		}


	}	

					
			break;

			case 3:
		
			printf("\nEnter the name to be deleted:");
			scanf("%s",sea);
			for(i=0;i<size;i++)
			{

				
					for(j=0;j<s[i];j++)
		{				
						for(k=0;k<s1[i][j];k++)

				{ 
					if(strcmp(sea,dir3[i][j][k])==0)
				 { 	for(t=k;t<<s1[i][j];t++)	
				 	{
				 		strcpy(dir3[i][j][t+1],dir3[i][j][t]);
						
					}
					
					(s1[i][j])--;	
						break;
					}
				}				
					break;	
				}

			}
			

	printf("\nLevel : %s",dir);
	for(i=0;i<size;i++)
	{	printf("\nDirectory %d : %s",i,dir1[i]);
		for(j=0;j<s[i];j++)
		{
			printf("\nSub-Dired %d : %s",j,dir2[i][j]);
		
			for(k=0;k<s1[i][j];k++)
			{
				printf("\nFile name %d : %s",j,dir3[i][j][k]);		
			}
		}


	}	


			

				break;
				case 4:
				printf("\nLevel : %s",dir);
	for(i=0;i<size;i++)
	{	printf("\nDirectory %d : %s",i,dir1[i]);
		for(j=0;j<s[i];j++)
		{
			printf("\nSub-Dired %d : %s",j,dir2[i][j]);
		
			for(k=0;k<s1[i][j];k++)
			{
				printf("\nFile name %d : %s",j,dir3[i][j][k]);		
			}
		}


	}	
				
				break;
				default:
				break;

		}

		printf("\nDo you want to continue:(1/0)");
				scanf("%d",&ch);


	}while(ch==1);


}
