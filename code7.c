/*Tu Mai 
1001594173*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ListLib.h"
#include "QueueLib.h"
#include "StackLib.h"
#include "BSTLib.h"
#define SIZE 100

void ReadInFile(char *argv[], char ParamName[], char ParamValue[])
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

int main(int argc[], char *argv[])
{
	// file handling
	FILE *ReceiptFile, *QueueFile, *ZipFile;
	char ReceiptInput[SIZE] = {};
	char QueueFileName[SIZE ] = {};
	char ZipFileName[SIZE] = {};
	ReadInFile(argv, "RECEIPTNUMBER=", ReceiptInput);
	ReadInFile(argv, "QUEUE=", QueueFileName);
	ReadInFile(argv, "ZIPFILE=", ZipFileName);
	
	char SeatMapArray[26][20];
	int ReceiptNumber = atoi(ReceiptInput);
	
	// Create Queue
	QueueFile = fopen(QueueFileName, "r");
	if(ferror(QueueFile))
	{
		perror("\nError opening Queue File: ");
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
	if(ferror(ZipFile))
	{
		printf("\nError opening Zip File: ");
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
	char SeatMapFileName[SIZE ] = {};
	int theaterNeeded = 1;
	int row, column;
	char SeatMapLine[600] = {};
	char fileDimensions[6];
	int numTickets;
	char seatChoice[3];
	char choiceRow;
	int choiceSeat;
	char tempSeat[2];
	LNODE *LinkedListHead;
	LNODE *TempPtr = NULL;
	SNODE *StackTop = NULL;
	char returnedTicket[3];
	
	while(QueueHead->next_ptr != NULL)
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
					LinkedListHead = NULL;
					while(theaterNeeded)
					{
						printf("Pick a theater by entering a zipcode\n\n");
						InOrder(root);
						printf("\n\nEnter zip ");
						scanf("%s", zipChoice);

						choiceNode = SearchForBNODE(root, zipChoice);
						strcpy(SeatMapFileName, choiceNode->FileName);
						
						// Read seat map file and create Seat Map
						SeatMapFile = fopen(SeatMapFileName, "r");
						fgets(SeatMapLine, sizeof(SeatMapLine), SeatMapFile);
						fclose(SeatMapFile);
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
						if(strlen(seatChoice) == 3) // checks in case choiceSeat is a two digit number
						{
							tempSeat[0] = seatChoice[1];
							tempSeat[1] = seatChoice[2];
							choiceSeat = atoi(tempSeat);
						}
						else
						{
							choiceSeat = seatChoice[1] - '0';
						}
						choiceRow = toupper(seatChoice[0]);
						
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
							InsertNode(&LinkedListHead, seatChoice);
							
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
							
							SeatMapFile = fopen(SeatMapFileName, "w");
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
					push(&StackTop, LinkedListHead, ReceiptNumber++, choiceNode->MovieTheaterName);
					printf("\n\nEnjoy your movie %s\n", QueueHead->Name);
					deQueue(&QueueHead);
					
					choiceNeeded = 0;
					break;
				case 2: // See who's in line
					DisplayQueue(QueueHead);
					
					choiceNeeded = 0;
					break;
				case 3: // See seat map for a given theater
					printf("\n\nPick a theater by entering a zipcode\n\n");
					InOrder(root);
					printf("\n\nEnter zip ");
					scanf("%s", zipChoice);
					
					choiceNode = SearchForBNODE(root, zipChoice);
					strcpy(SeatMapFileName, choiceNode->FileName);
					
					// Read seat map file and create Seat Map
					SeatMapFile = fopen(SeatMapFileName, "r");
					fgets(SeatMapLine, sizeof(SeatMapLine), SeatMapFile);
					fclose(SeatMapFile);
					strcpy(fileDimensions, choiceNode->Dimensions);
					
					Token = strtok(fileDimensions, "x");
					row = atoi(Token);
					Token = strtok(NULL, "x");
					column = atoi(Token);
					
					int c,d;
					printf("\n\n%-8s", " ");
					for(c = 1; c < column+1; c++)
					{
						printf("Seat%d  ", c);
					}
					printf("\n");
					for(c = 0; c < row; c++)
					{
						printf("Row %c\t", c+65);
						for(d = 0; d < column; d++)
						{
							printf("%-7s", "O");
						}
						printf("\n");
					}
				
					choiceNeeded = 0;
					break;
				case 4: // Print today's receipts

					printf("\n\nToday's Receipts\n");
					if(StackTop == NULL)
					{
						printf("\n\nToday's tickets have already been displayed\n\n");
					}
					else
					{
						while(StackTop != NULL)
						{
							printf("\n\nReceipt #%d\n\n", StackTop->ReceiptNumber);
							printf("\t%s\n\n", StackTop->MovieTheaterName);
							while(StackTop->TicketList != NULL)
							{
								ReturnAndFreeLinkedListNode(&(StackTop->TicketList), returnedTicket);
								returnedTicket[0] = toupper(returnedTicket[0]);
								printf("\t%s", returnedTicket);
							}
							pop(&StackTop);
						}
					}
					
				
					choiceNeeded = 0;
					break;
				default: 
					printf("Choice invalid. Please reenter.\n\n");
			}
		}
	}
	
	printf("\nGood job! You sold tickets to all the customers in line.\n");
	printf("\n\nToday's Receipts\n");
	if(StackTop == NULL)
	{
		printf("\n\nToday's tickets have already been displayed\n\n");
	}
	else
	{
		while(StackTop != NULL)
		{
			printf("\n\nReceipt #%d\n\n", StackTop->ReceiptNumber);
			printf("\t%s\n\n", StackTop->MovieTheaterName);
			while(StackTop->TicketList != NULL)
			{
				ReturnAndFreeLinkedListNode(&(StackTop->TicketList), returnedTicket);
				returnedTicket[0] = toupper(returnedTicket[0]);
				printf("\t%s", returnedTicket);
			}
			pop(&StackTop);
		}
	}
	printf("\n");
	
	
	return 0;
}