/* Tu  Mai 
1001594173 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "StackLib.h"

void push(SNODE **StackTop, LNODE *LinkedListHead, int receiptNum, char theaterName[])
{
	SNODE *NewNode = malloc(sizeof(SNODE));
	NewNode->ReceiptNumber = receiptNum;
	strcpy(NewNode->MovieTheaterName,theaterName);
	NewNode->TicketList = LinkedListHead;
	NewNode->next_ptr = NULL;
	
	if(*StackTop == NULL)
	{
		*StackTop = NewNode;
	}
	else
	{
		NewNode->next_ptr = *StackTop;
		*StackTop = NewNode;
	}
}

void pop(SNODE **StackTop)
{
	SNODE *TempPtr = *StackTop;
	
	if(*StackTop == NULL)
	{
		printf("\n\nStack empty\n\n");
	}
	else
	{
		free(*StackTop);
		*StackTop = TempPtr->next_ptr;
	}
}