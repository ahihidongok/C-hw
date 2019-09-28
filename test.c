#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ListLib.h"
#include "QueueLib.h"
#include "StackLib.h"
#include "BSTLib.h"
void pop(SNODE **StackTop)
{
	SNODE *TempPtr = *StackTop;
	if (*StackTop == NULL)
	{
		printf("Pop not executed - stack is empty\n\n");
	}
	else
	{
		free(*StackTop);
		*StackTop = TempPtr->next_ptr;
	}
}

void push(SNODE **StackTop, LNODE *TicketList, int ReceiptNum, char TheaterName[])
{
	SNODE *NewNode = malloc(sizeof(SNODE));
	NewNode->ReceiptNumber = ReceiptNum;
	strcpy(NewNode->MovieTheaterName,TheaterName);
	NewNode->TicketList = NULL;
	NewNode->next_ptr = NULL;
	if (*StackTop == NULL)
	{
		*StackTop = NewNode;
	}
	else
	{
		NewNode->next_ptr = *StackTop;
		*StackTop = NewNode;
	}
}

void enQueue(char Name[], QNODE **QueueHead, QNODE **QueueTail)
{
	QNODE *NewNode = malloc(sizeof(QNODE));
	strcpy(NewNode->Name,Name);
	NewNode->next_ptr = NULL;
/* Queue is empty */
	if (*QueueHead == NULL)
	{
		*QueueHead = *QueueTail = NewNode;
	}
	else
	{
		(*QueueTail)->next_ptr = NewNode;
		*QueueTail = NewNode;
	}
}

void deQueue(QNODE **QueueHead)
{
	QNODE *TempPtr = (*QueueHead)->next_ptr;
	if (*QueueHead == NULL)
	{
		printf("Queue is emtpy\n\n");
	}
	else
	{
		free(*QueueHead);
		*QueueHead = TempPtr;
	}
}

void DisplayQueue(QNODE *QueueHead)
{
	QNODE *TempPtr = QueueHead;
	while (TempPtr != NULL)
	{
		printf(" %s\n", TempPtr->Name);
		TempPtr = TempPtr->next_ptr;
	}
}

void ReturnAndFreeLinkedListNode (LNODE **TicketBox, char TicketIn[])
{
	LNODE *TempPtr, *PreviousNode; 
	TempPtr = *TicketBox; 
	
	while(TempPtr != NULL )
	{
		if(TempPtr->Ticket == TicketIn)
		{
			if (TempPtr == *TicketBox)
			{
				*TicketBox = TempPtr->next_ptr; 
			}
			else
			{
				PreviousNode->next_ptr = TempPtr->next_ptr;
			}
			free(TempPtr);
		}
		else
		{
			PreviousNode = TempPtr; 
			TempPtr = TempPtr->next_ptr;
		}
	}
}

//void AddBSTNode(BNODE **current_node, )
void AddBSTNode(BNODE **CurrentNode, char theaterName[], char zipCode[], char fileName[], char dimensions[])
{
	if(*CurrentNode == NULL)
	{
		*CurrentNode = (BNODE *)malloc(sizeof(BNODE));
		(*CurrentNode)->left = (*CurrentNode)->right = NULL;
		strcpy((*CurrentNode)->MovieTheaterName, theaterName);
		strcpy((*CurrentNode)->ZipCode, zipCode);
		strcpy((*CurrentNode)->FileName, fileName);
		strcpy((*CurrentNode)->Dimensions, dimensions);
	}
	else
	{
		if(strcmp(zipCode, (*CurrentNode)->ZipCode) < 0) // zipcode less than node value
		{
			AddBSTNode(&(*CurrentNode)->left, theaterName, zipCode, fileName, dimensions);
		}			
		else if(strcmp(zipCode, (*CurrentNode)->ZipCode) > 0) // zipcode greater than node value
		{
			AddBSTNode(&(*CurrentNode)->right, theaterName, zipCode, fileName, dimensions);
		}
		else
		{
			printf("\n\nDuplicate Element!! Not Allowed!!\n\n");
		}
	}
}
void InsertNode(LNODE **TicketHead, char Ticket[])
{
	LNODE *NewNode, *TempPtr;
	NewNode = (LNODE*)malloc(sizeof(LNODE));
	NewNode->next_ptr = NULL;
	strcpy(NewNode->Ticket,Ticket);
	
	if (*TicketHead == NULL)		
	{
		*TicketHead = NewNode;
	}
	else
	{
		TempPtr = *TicketHead;
		/* Traverse the linked list to find the end node */
		while (TempPtr->next_ptr != NULL)
			TempPtr = TempPtr->next_ptr;
		/* Change end node to point to new node */
		TempPtr->next_ptr = NewNode;
		
	}
}
void InOrder (BNODE *TreeNode)
{
	if(TreeNode != NULL )
	{
		InOrder(TreeNode->left);
		printf("%-40s %s\n", TreeNode->MovieTheaterName, TreeNode->ZipCode);
		InOrder(TreeNode->right);
	}
}
BNODE* SearchForBNODE(BNODE *root, char zipChoice[])
{
	if(root == NULL || (strcmp(root->ZipCode, zipChoice) == 0))
	{
		return root; 
	}
	if(strcmp(zipChoice, root->ZipCode) >0)
	{
		return SearchForBNODE(root->right, zipChoice);
	}
	return SearchForBNODE(root->left, zipChoice);
}

void ReadCommandLineParameter(char *argv[], char ParamName[], char ParamValue[])
{
	int i = 0;
	while (argv[++i] != NULL)
	{
		if(!strncmp(argv[i], ParamName, strlen(ParamName)))
		{
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
		}
	}
	return;
}

int main(int argc, char *argv[])
{
	// file handling
	FILE *ReceiptFile, *QueueFile, *ZipFile;
	char ReceiptFileName[100] = {};
	char QueueFileName[100] = {};
	char ZipFileName[100] = {};
	ReadCommandLineParameter(argv, "RECEIPTNUMBER=", ReceiptFileName);
	ReadCommandLineParameter(argv, "QUEUE=", QueueFileName);
	ReadCommandLineParameter(argv, "ZIPFILE=", ZipFileName);
	
	char SeatMapArray[26][20];
	
	// Create Queue
	QueueFile = fopen(QueueFileName, "r");
	if(QueueFile == NULL)
	{
		printf("\n\nError Opening Queue File.\n\n");
		exit(0);
	}
	
	char lineQueue[30];
	int QueueCount = 0;
	QNODE *QueueHead = NULL;
	QNODE *QueueTail = NULL;
	while(fgets(lineQueue, sizeof(lineQueue), QueueFile) != NULL)
	{
		enQueue(lineQueue, &QueueHead, &QueueTail);
		QueueCount++;
	}
	fclose(QueueFile);
	
	// Create Binary Search Tree
	ZipFile = fopen(ZipFileName, "r");
	if(ZipFile == NULL)
	{
		printf("\n\nError Opening Zip File.\n\n");
		exit(0);
	}
	
	char lineBST[500];
	BNODE *root = NULL;
	char *Token;
	char tempName[40];
	char tempZipCode[6];
	char tempFileName[100];
	char tempDimensions[6];

	
	while(fgets(lineBST, 499, (FILE *)ZipFile) != NULL)
	{
		Token = strtok(lineBST, "|");
		strcpy(tempName, Token);
		
		Token = strtok(NULL, "|");
		if(Token != NULL)
		{
			strcpy(tempZipCode, Token);
			Token = strtok(NULL, "|");
		}	

		if(Token != NULL)
		{
			strcpy(tempFileName, Token);
			Token = strtok(NULL, "|");
		}		

		if(Token != NULL)
		{
			strcpy(tempDimensions, Token);
		}
		AddBSTNode(&root, tempName, tempZipCode, tempFileName, tempDimensions);
	}
	
	fclose(ZipFile);
	
	// menu
	int choice = 0;
	int choiceNeeded = 1;
	
	// variables for case 1
	char zipChoice[6] = {};
	BNODE *choiceNode;
	FILE *SeatMapFile;
	char SeatMapFileName[100] = {};
	int theaterNeeded = 1;
	int row, column;
	char SeatMapLine[600] = {};
	char fileDimensions[6];
	int numTickets;
	char seatChoice[3];
	char choiceRow;
	int choiceSeat;
	
	while(QueueHead != NULL)
	{	
		choiceNeeded = theaterNeeded = 1;
		printf("\n\n1. Sell tickets to next customer\n\n2. See who's in line\n\n3. See the seat map for a given theater\n\n4. Print today's receipts\n\n");
		while(choiceNeeded)
		{
			printf("Choice: ");
			scanf("%d", &choice);
			
			switch(choice)
			{
				case 1: // Sell tickets to next customer
					
					// Get theater node
					printf("\n\nHello %s\n\n", QueueHead->Name);
					while(theaterNeeded)
					{
						printf("Pick a theater by entering a zipcode\n\n");
						InOrder(root);
						printf("\n\nEnter zip ");
						scanf("%s", zipChoice);

						choiceNode = SearchForBNODE(root, zipChoice);
						strcpy(SeatMapFileName, choiceNode->FileName);
						
						// Read seat map file and create Seat Map
						SeatMapFile = fopen(SeatMapFileName, "r+");
						fgets(SeatMapLine, sizeof(SeatMapLine), SeatMapFile);
						strcpy(fileDimensions, choiceNode->Dimensions);
						
						Token = strtok(fileDimensions, "x");
						row = atoi(Token);
						Token = strtok(NULL, "x");
						column = atoi(Token);
						if(strlen(SeatMapLine)-2 > (row*column))
						{
							printf("Seat Map File exceeds theater's dimensions. Please pick another theater.\n");
						}
						else
						{
							theaterNeeded = 0;
						}
					}
					int a;
					printf("\n\n%-8s", " ");
					for(a = 1; a < column+1; a++)
					{
						printf("Seat%d  ", a);
					}
					
					int i,j;
					int k = 0;
					printf("\n");
					while(k < (row*column))
					{
						for(i = 0; i < row; i++)
						{
							printf("Row %c\t", i+65);
							for(j = 0; j < column; j++)
							{
								SeatMapArray[i][j] = SeatMapLine[k];
								k++;
								printf("%c%6s", SeatMapArray[i][j], "");
							}
							printf("\n");
						}
					}

					
					// Sell Tickets and mark off seats
					printf("\n\nHow many tickets do you want to buy? ");
					scanf("%d", &numTickets);
					int b;
					for(b = 0; b < numTickets; b++)
					{
						printf("\n\nPick a seat (Row Seat) ");
						scanf("%s", seatChoice);
						choiceRow = toupper(seatChoice[0]);
						choiceSeat = seatChoice[1] - '0';
						
						if((choiceRow-65)>row || choiceSeat>column)
						{
							printf("This is not a valid seat. Please choose again.");
							b--;
						}
						else if(SeatMapArray[choiceRow-65][choiceSeat-1] == 'X')
						{
							printf("Seat %c-%d is not available.\n", choiceRow, choiceSeat);
							b--;
						}
						else
						{
							SeatMapArray[choiceRow-65][choiceSeat-1] = 'X';
							
							int x,y;
							int z = 0;
							for(x = 0; x < row; x++)
							{
								for(y = 0; y < column; y++)
								{
									SeatMapLine[z] = SeatMapArray[x][y];
									z++;
								}
							}
							
							printf("\n\n%s\n\n", SeatMapLine);
							fprintf(SeatMapFile, "%s", SeatMapLine);
							fclose(SeatMapFile);
							
							printf("\n\n%-8s", " ");
							for(a = 1; a < column+1; a++)
							{
								printf("Seat%d  ", a);
							}
							printf("\n");
							for(i = 0; i < row; i++)
							{
								printf("Row %c\t", i+65);
								for(j = 0; j < column; j++)
								{
									printf("%c%6s", SeatMapArray[i][j], "");
								}
								printf("\n");
							}
						}
					}
					printf("\n\nEnjoy your movie %s\n", QueueHead->Name);
					deQueue(&QueueHead);
					
					choiceNeeded = 0;
					break;
				case 2: // See who's in line
					DisplayQueue(QueueHead);
					choiceNeeded = 0;
					break;
				case 3: // See seat map for a given theater
					choiceNeeded = 0;
					break;
				case 4: // Print today's receipts
					choiceNeeded = 0;
					break;
				default: 
					printf("Choice invalid. Please reenter.\n\n");
			}
		}
	}
	
	
	return 0;
}