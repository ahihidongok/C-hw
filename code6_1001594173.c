/*Tu Mai 
1001594173*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include"ListLib.h"
#define SIZE 20
#define BUFSIZE 50


void PrintList ( CommandStruct **head)
{
	CommandStruct *temp_ptr;
	temp_ptr = *head;
	while(temp_ptr != NULL)
	{
		printf(" %s  %s\n",temp_ptr->letter,temp_ptr->command);
		temp_ptr = temp_ptr->next_ptr;
	}
	printf("\n\n\n");
}

void ReadInFile(char *argv[], char ParamName[], char ParamValue[])
{
	int i = 0;
	while (argv[++i] != NULL)
	{
		if (!strncmp(argv[i], ParamName, strlen(ParamName)))
		{
			
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
		}
	}
	//printf("%s\n", ParamValue);
	return;
}
void PrintArray(char myArray[][SIZE], int userSize)
{
	int i,j;
	printf("\n");
	for (i=0; i<userSize; i++)
	{
		for (j=0; j<userSize; j++)
		{
			printf(" %c", myArray[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}


void DrawLine (char myArray[][SIZE], int row, int column, char drawCommand, int size, char markCharacter)
{
	int i;
	if(drawCommand == 'H' || drawCommand == 'h')
	{
		for(i=column; i<size+column; i++)
		{
			myArray[row][i] = markCharacter;
		}
	}
	else if (drawCommand == 'V' || drawCommand == 'v')
	{
		for (i=row; i<size+row; i++)
		{
			myArray[i][column] = markCharacter;
		}
	}
}

void Draw (char myArray[][SIZE], char drawCommand, int row, int column, int size, char markCharacter)
{
	int userSize = 20; 
	
	if(markCharacter == ' ' || markCharacter == '\n')
	{
		markCharacter = 'X';
	}
	if (drawCommand == 'Q' || drawCommand == 'q')
	{
		printf("\n");
		//programRunning = 0;
	}
	else if (drawCommand == 'p' || drawCommand == 'P')
	{
		if ((row <= userSize) && (column <= userSize) && (row>= 0) && (column >=0))
		{
			myArray[row][column] = markCharacter; 
			//PrintArray(myArray, userSize);
		}
		else
		{
			printf("That draw command is out of range. \n");
		}
	}
	else if (drawCommand == 'H' || drawCommand == 'h')
	{
		if(((size+column) <= userSize) && (row >= 0) && (column >=0) && (size>0))
		{
			DrawLine (myArray, row, column, drawCommand, size, markCharacter);
			//PrintArray(myArray, userSize);
		}
		else
		{
			printf("That draw command is out of range. \n");
		}
	}
	else if (drawCommand == 'V' || drawCommand == 'v')
	{
		if(((size+row) <= userSize) && (row >= 0) && (column >=0) && (size>0))
		{
			DrawLine (myArray, row, column, drawCommand, size, markCharacter);
			//PrintArray(myArray, userSize);
		}
		else
		{
			printf("That draw command is out of range. \n");
		}
	}
	else
	{
		printf("That draw command is unknown.\n");
	}
}

int main(int argc, char*argv[])
{	
	char inputfilename[20] = "";
	//open the INPUT FILE 
	if(inputfilename == NULL )
	{
		printf("The file name is NULL \n");
	}
	if (argc < 2)
	{
		printf("Wrong parameter number, use the following format to run\n");
		printf("a.out  DCFILE=inputfile.txt\n");
		exit(0);
	}
	
	ReadInFile(argv,"DCFILE=",inputfilename);
	//printf("I'm here %s\n", inputfilename);
	
	if(inputfilename == NULL)
	{
		printf("Cannot open file %s\n",argv[0]);
		printf("Wrong parameter number, use the following format to run\n");
		printf("%s  DCFILE=inputfile.txt\n",argv[0]);
		exit(0);
	}
	
	
	
	//Code to ask user to input then draw 
	char myArray[SIZE][SIZE];
	int userSize = 0; 
	int needSize = 1; 
	char userChar; 
	FILE *fi;
	char buff[BUFSIZE];
	CommandStruct *head = NULL;
	char *token;
	CommandStruct *NewNode;
	int done = 0; 
	
	fi = fopen(inputfilename, "r");
	if (fi == NULL)
	{
		printf("There's an error opening input file\n");
		return -1;
	}
	
	while(fgets(buff,BUFSIZE-1,fi) != NULL)
	{
		if(ferror(fi))
		{
			perror("Error is ");
			break;
				
		}
		else
		{
			NewNode = (CommandStruct*)malloc(sizeof(CommandStruct)); //malloc  return void pointer
			NewNode->next_ptr = NULL;
			strcpy(NewNode->letter,strtok(buff,"|"));
			strcpy(NewNode->command,strtok(NULL,"|"));
			//AddNodeAtEnd(NewNode,&head); 
			AddNode(NewNode->letter[0],NewNode->command,&head);
			
		}
	
	}	
	
	//PrintList(&head);
	close(fi);
	char inputletter[SIZE];
	int invalidinput = 1; 
	
	while(invalidinput)
	{
		printf("Please enter 1-3 letters ");
		scanf("%s",&inputletter);
		
		if(strlen(inputletter)>3)
			printf("\nEntry not valid. Please try again\n");
		else
			invalidinput = 0;
	}
	int m;
	for (m =0; m<3;m++)
	{
		inputletter[m] = toupper(inputletter[m]);
	}
	
	CommandStruct *Node; 
	
	
	
	while(0)
	{
		
	}
	
	
	userSize = SIZE;
	
	
	
	//prompt user for background character 
	printf("What is the background character? ");
	scanf(" %c",&userChar);
	int i;
	int j;
	for (i=0 ; i<userSize; i++)
	{
		for (j=0; j<userSize; j++)
		{
			myArray[i][j] = userChar;
		}
	}
	
	//print out TOOL INSTRUCTION 
	
	//PrintArray (myArray, userSize);
	
	//enter a draw command 
	int programRunning = 1; 
	char drawCommand;
	int row; 
	int column;
	int size; 
	char markCharacter; 
	i=0;

	while(programRunning)
	{
		//printf("Processing this letter %c", inputletter[i]);
		while(inputletter[i] != '\0') 
		{
			
			Node = head;
			char command[SIZE];
		
			while(Node !=NULL)
			{

				//if(Node->letter[0]==inputletter[i])
				Node = searchNode(Node,inputletter[i]);
				if(Node != NULL)
				{
					sscanf(Node->command," %c(%d,%d,%d)%c", &drawCommand, &row, &column, &size, &markCharacter);
					//sscanf(command," %c(%d,%d,%d)%c", &drawCommand, &row, &column, &size, &markCharacter);
					//printf(" %c %d %d %d %c\n", drawCommand, row, column, size, markCharacter);
					
					if(i == 0)
					{
						Draw ( myArray,drawCommand, row, column,size,markCharacter);
					}
					else if (i == 1)
					{
						Draw ( myArray,drawCommand, row, column+7,size,markCharacter);
					}
					else if ( i == 2)
					{
					
						Draw ( myArray,drawCommand, row, column+14,size,markCharacter);
					}
					
				}
			
				Node = Node->next_ptr;
	
			}

			i++;
			
		}
		
		PrintArray(myArray, userSize);
		
		
		return 0; 
		
		
	}
	
}

