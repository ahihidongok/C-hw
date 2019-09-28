/* Tu Mai 
1001594173*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "QueueLib.h"

void enQueue(char CustomerName[], QNODE **QueueHead, QNODE **QueueTail)
{
	QNODE *NewNode = malloc(sizeof(QNODE));
	strcpy(NewNode->Name, CustomerName);
	NewNode->next_ptr = NULL;
	
	if(*QueueHead == NULL)
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
	
	if(*QueueHead == NULL)
	{
		printf("\n\n***QUEUE EMPTY***\n\n");
	}
	else
	{
		free(*QueueHead);
		*QueueHead = TempPtr;
	}
}

void DisplayQueue(QNODE *QueueHead)
{
	printf("\n\nCustomer Queue\n\n");
	QNODE *TempPtr = QueueHead;
	
	while(TempPtr != NULL)
	{
		printf("%s", TempPtr->Name);
		TempPtr = TempPtr->next_ptr;
	}
}

