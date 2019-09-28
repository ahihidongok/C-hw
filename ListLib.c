/*Tu Mai 
1001594173*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ListLib.h"

void InsertNode(LNODE **LinkedListHead, char CurrentTicket[])
{
	LNODE *TempPtr, *PrevPtr, *NewNode;
	PrevPtr = NULL;
	TempPtr = *LinkedListHead;
	
	while(TempPtr != NULL && (strcmp(TempPtr->Ticket, CurrentTicket) < 0))
	{
		PrevPtr = TempPtr;
		TempPtr = TempPtr->next_ptr;
	}
	
	NewNode = malloc(sizeof(LNODE));
	strcpy(NewNode->Ticket, CurrentTicket);
	NewNode->next_ptr = TempPtr;
	
	if(PrevPtr == NULL)
	{
		*LinkedListHead = NewNode;
	}
	else
	{
		PrevPtr->next_ptr = NewNode;
	}

}

void ReturnAndFreeLinkedListNode(LNODE **TicketList, char currentTicket[])
{
	strcpy(currentTicket, (*TicketList)->Ticket);
	free(*TicketList);
	*TicketList = (*TicketList)->next_ptr;
}

