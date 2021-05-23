#include "assignment_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define elem -91919

static int fill(int ,int );		//used to fill the array 
static void bubble(int , int ); //insert the winning team in the array after comparison 
static void display_2(int ,int ); //displays the element of the array
static void empty(int row_no, int size); //checks if the row is empty or not
static void compare(int m, int size); //the comparison between the two elements occurs here
static void rec_bubble(int , int );	//if next row is filled then bubble the elements to the next row recursively
static void final_comp(int );	//final comparison of the elements left in the array to find the second largest element
int **arr;	//array to store the winning members

static int fill(int row_no,int size)//checks if the row is filled or not
{
	int check=1;
	for(int j=0;j<size;j++)
	{
		if(arr[row_no][j]!=elem)
		{
			check =0;
			break;
		}
	}
	return check;
}
static void display_2(int i,int size) //displays the elements of the process
{
	for(int j=0;j<size;j++)
	{
		if(arr[i][j]!=elem)
			printf("%d ",arr[i][j]);
		else
			break;
	}
}
static void empty(int row_no, int size)	//checks if the row is empty or not
{
	for(int j=0;j<size;j++)
		arr[row_no][j]=elem;
}
static void compare(int m, int size)
{
	if(fill(0,size)==1) // if the first row is empty then store the element there
		arr[0][0]=m;
	else
		bubble(m,size);		//if the first row is not empty then it sends for the comparison of the two elements
}
static void bubble(int m, int size)
{
	int i=0; ;
	int k=i+1;
			if(arr[i][0]>m)		//the 1st comparison between the elements 
			{
				printf("%d x %d = %d %d\n",arr[i][0],m,arr[i][0],m);
					if(fill(k,size)==1) //after stores the winning elements in the next row
					{
						arr[k][0] = arr[i][0];
						arr[k][1] = m;
						empty(i,size);  //empties the row after the comparison
					}
					else		
					{
						arr[0][1] = m;
						rec_bubble(0,size);		//if the row is filled then match happens between then shifts to the next row
					}
			}
			else
			{
				printf("%d x %d = %d %d\n",arr[i][0],m,m,arr[i][0]);
					if(fill(k,size)==1)
					{
						arr[k][0] = m;
						arr[k][1] = arr[i][0];
						empty(i,size);		//empties the row after the comparison
					}
					else
					{
							arr[0][1]=arr[0][0];
							arr[0][0]=m;
						rec_bubble(0,size);		//if the row is filled then match happens between then shifts to the next row
					}
			}
}	
static void rec_bubble(int row_no, int size)//if the row where the elements are to be inserted is filled then match happens  and  is shifted to the next row
{
	int k=0;
	for(int j=0;j<size;j++)
	{
		if(arr[row_no][j]!=elem)
			k++;//no of elements in the row
	}
	if(k>row_no+1)
	{
		if(fill(row_no+1,size)==1)//checks if the row is empty or not
		{
			for(int i=0;i<k;i++)
				arr[row_no+1][i]=arr[row_no][i];
			empty(row_no,size);
		}
		else
		{
			if(arr[row_no][0]>arr[row_no+1][0]) //comparison between the first element of the row with the first element of the next row
			{
				display_2(row_no+1,size);
				printf("x ");
				display_2(row_no,size);
				printf("= ");
				int x = arr[row_no+1][0];		
				arr[row_no+1][0]=arr[row_no][0];
				arr[row_no+1][1]=x;
				x=k-1; int i=2; int j=1;
				while(x>0)		//shifts the winning elements to the next row
				{
					arr[row_no+1][i]=arr[row_no][j];
					i++; j++;
					x--;
				}
				display_2(row_no+1,size);
				printf("\n");
				empty(row_no,size);  //empties the previous row
			}
			else
			{
				display_2(row_no+1,size);
				printf("x ");
				display_2(row_no,size);
				printf("= ");
				for(int i=row_no+2;i>=2;i--)		//shifts the winning elements to the next row
					arr[row_no+1][i]=arr[row_no+1][i-1];
				arr[row_no+1][1]=arr[row_no][0];
				display_2(row_no+1,size);
				printf("\n");
				empty(row_no,size); //empties the previous row
			}
			rec_bubble(row_no+1,size); //recursively call the function until the element which has undergone i comparisons is in the ith row
		}
	}
	else
		return;
}



static void final_comp(int size)
{//match between the remaining elements of the array
	for(int i=0;i<size-2;i++)
	{
		if(fill(i,size)==0)
		{
			int j=i+1;
			while(fill(j,size)!=0 && j<size)
				j++;
			display_2(j,size);
			printf("x ");
			display_2(i,size);
			printf("= ");
			if(arr[i][0]>arr[j][0]) //comparison between the first element of the rows happens to find the winning members
			{
				int x=arr[j][0];
				empty(j,size);
				arr[j][0]=arr[i][0];
				arr[j][1]=x;
				for(int k=1;k<size;k++)
				{
					if(arr[i][k]!=elem)			//checks if the row is filled or not
						arr[j][k+1]=arr[i][k];
					else
						break;
				}
				empty(i,size);
				display_2(j,size);
				printf("\n");
			}
			else
			{
				int k=0;
				for(int c=0;c<size;c++)
				{
					if(arr[j][c]!=elem) 	//checks if the row is filled or not
						k++;
					else
						break;
				}
				for(int c=k;c>=2;c--)
					arr[j][c]=arr[j][c-1];
				arr[j][1] = arr[i][0];
				display_2(j,size);
				empty(i,size);
				printf("\n");
			}
		}
	}
	for(int i=0;i<size;i++)// displays the second largest number
	{
		if(fill(i,size)==0)
		{
			int sec_max = arr[i][1];
			for(int j=2;j<size;j++)
			{
				if(arr[i][j]!=elem && arr[i][j]>sec_max)  //comparison between the elements of the last row to find the second largest number
					sec_max = arr[i][j];
			}
			printf("\n");
			printf("%d\n",sec_max);
			break;
		}
	}
}
void find_second_greatest(int *numbers, int length)
{
	double len = log(length)/log(2); 
	int size = ceil(len) +1;	//set the dimension of the array to the log of the length of the given array
	//size++;
	arr = (int **)malloc(size * sizeof(int*));
	for (int i=0; i<size; i++) 
         arr[i] = (int *)malloc(size * sizeof(int));

    for(int i=0;i<size;i++) // to initialize the array
    {
    	for(int j=0;j<size;j++)
    		arr[i][j]=elem;
    }
    for(int i=0;i<length;i++)
    	compare(numbers[i],size); //compares the two elements of the array and prints the winner
    final_comp(size);	// to find the second largest element from the remaining elements
}
