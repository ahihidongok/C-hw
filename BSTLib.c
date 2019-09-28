/*Tu Mai
1001594173*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "BSTLib.h"

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

void InOrder(BNODE *TreeNode)
{
	if(TreeNode != NULL)
	{
		InOrder(TreeNode->left);
		printf("%-40s %s\n", TreeNode->MovieTheaterName, TreeNode->ZipCode);
		InOrder(TreeNode->right);
	}
}


BNODE* SearchForBNODE(BNODE *root, char zipChoice[])
{
	if(root == NULL || (strcmp(root->ZipCode,zipChoice) == 0))
	{
		return root;
	}
	if(strcmp(zipChoice, root->ZipCode) > 0) // zip greater than root zip
	{
		return SearchForBNODE(root->right, zipChoice);
	}
	return SearchForBNODE(root->left, zipChoice);
}

