/*
Tu Mai 
1001594173*/
#include<stdio.h>
#define SIZE 20

void printArray (int length, char array[][length])
	
{ 	
	
	int i,j;
	for(i=0;i<length;i++)
	{	for(j=0;j<length;j++)
		{
			printf(" %c",array[i][j]);
		}
		printf("\n");
	}
	return;	
}
void initializeArray (int length ,char array[][length], char inputchar)
	{
	int i,j;
	for (i=0;i<length;i++)
	{	for (j =0; j<length;j++)
		{
			array[i][j] = inputchar;
		
		}
	}
	
	
	printArray(length,array);
	return;
}
void vertical (int row, int collum, int size,int length, char array[][length], char newchar)
{
	int i;
	for (i=row;i<size+row;i++)
	{
		array[i][collum] = newchar;
	}
}
void horizontal (int row, int collum, int size,int length, char array[][length], char newchar)
{
	int i;
	for (i=collum;i<size+collum;i++)
	{
		array[row][i] = newchar;
	}
}
void point (int row, int collum, int size,int length, char array[][length], char newchar)
{

		array[row][collum] = newchar;

}


int main(void)
{	
	int arraylength = 20; 
	int length;
	int inputvalid = 1;
	char inputchar;
	char array[SIZE][SIZE];
	int notquit = 1;
	
	while (inputvalid)
	{	
		printf("How big is the array? (Enter a value between 1 and 20) ");
		scanf("%d", &length);
		if ((length>0) && (length<21))
		{
			inputvalid =0; 
		}
		else
		{	
			printf("\nThat value is outside of the max bounds of the array. Please reenter\t");
			inputvalid = 1;
			
		}
	}
	
	printf("What is the background character? ");
	scanf(" %c",&inputchar);
	initializeArray(length,array,inputchar);
	
	
	printf("\nDraw commands start with\n\n"
 	   	"\tP for a single point\n"
		"\tH for a horizontal line\n"
		"\tV for a vertical line\n\n"
		"After the P/V/H, enter a row,col coordinate and the number of spots to mark\n"
		"enclosed in () and separated by commas and then the character for the mark.\n"
		"'X' will be used if a mark is not entered. For example,\n\n"
 		"\tP(2,3,1)* \tstart at point 2,3 in the array and mark one spot\n"
 		"\t\t\twith an *. For P, the 3rd parameter is ignored.\n\n"
 		"\tV(1,2,3)$ \tstart at point 1,2 in the array and mark the next\n"
 		"\t\t\t3 spots down from the current position with $\n\n"
		"\tH(4,6,7)#\t start at point 4,6 in the array and mark the next\n"
		"\t\t\t7 spots to the right with #\n\n"
		"Coordinates out of range and lines drawn past the borders are not allowed.\n\n"
		"Enter Q at the draw command prompt to quit\n\n"
		"Press <ENTER> to continue\n\n");
		printArray(length,array);
	char command, newchar;
	int row, collum, size;
	int numofArgument = 0;
	while (notquit)
		{	
		newchar = ' ';
		row = 99;
		collum = 99; 
		size = 99;
		
		printf("Enter draw command (enter Q to quit) ");
		
		numofArgument = scanf(" %c(%d,%d,%d)", &command, &row, &collum, &size);
		newchar = getchar();
		
		printf("num of arg is %d %d\n", numofArgument, newchar);
		
		if (command == 'v' || command == 'V')
		{
			if ((row+size < length) && (row<length) && (collum<length) )
			{	
				
				if(newchar ==10)
				{	
					newchar = 'X';
				}
					
				vertical(row,collum,size,length,array,newchar);
				printArray(length,array);
				//printf("Enter Q at the draw command prompt to quit\n\n");
			}
			else
			{
				printf("That draw command is out of range\n\n");
				
			}
		}
		else if (command == 'h'||command == 'H')
		{	
			if ((collum+size < length) && (row<length) && (collum<length) )
			{	
				if(newchar == 10)
				{
					newchar = 'X';
				}
				horizontal(row,collum,size,length,array,newchar);
				printArray(length,array);
				
				//printf("Enter Q at the draw command prompt to quit\n\n");
			}
			else 
			{
				printf("That draw command is out of range\n\n");
			}
		}
		
		else if (command == 'p'|| command == 'P')
		{
			if((row<length) && (collum<length))
			{
				if(newchar == 10)
				{
					newchar = 'X';
				}
				point(row,collum,size,length,array,newchar);
				printArray(length,array);
				
			}
			else
			{
				printf("That draw command is out of range\n\n");
			}
		}
		
		else if (command == 'q' || command == 'Q')
		{
			notquit = 0;
		}
		 
		else
		{
			printf("That draw command is unknown\n\n");
		}
		
		
	}
	
	return 0;
	
}
