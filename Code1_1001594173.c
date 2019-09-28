/* Tu Mai 
   ID: 1001594173*/

#include <stdio.h>
int i = 0;
void ConvertDecimalToBinary(int DecimalNum, int binaryArray[]);
void PrintBinary(int binaryArray[]);

void ConvertDecimalToBinary(int DecimalNum, int binaryArray[])
{
	
	binaryArray[0] = DecimalNum;
	
	for(i = 1; i <= 7; i++)
	{
		binaryArray[i] = binaryArray[i - 1] >> 1;	
	}
	
	for(i = 0; i <= 7; i++)
	{
		binaryArray[i] = (binaryArray[i] & 1) ? 1 : 0;
	}

	return;
}

void PrintBinary(int binaryArray[])
{
	for (i = 7; i >= 0; i--)
	{
		printf("%d", binaryArray[i]);
	}
	return;
}

int main(void)
{
	int Decnum;
	int ValidNum = 1;
	int binaryArray[8];
	
	printf("Decimal to binary convertor\n\n");
	
	while (ValidNum)
	{
		printf("Please enter a decimal number between 0 and 255: ");
		scanf("%d", &Decnum);
	
		if (Decnum >= 0 && Decnum <= 255)
			ValidNum = 0;
		else
		{
			ValidNum = 1;
			printf("\nYou entered a number not between 0 and 255.\n\n");
		}
	}
	
	ConvertDecimalToBinary(Decnum, binaryArray);
	printf("\nDecimal %d converts to binary ", Decnum);
	PrintBinary(binaryArray);
	printf(".\n\n");

	return 0;
}
