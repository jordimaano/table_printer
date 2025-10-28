#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//still needs improvement
//needs to create separate functions for repetitive actions
//reduce cases (if/else)
//reduce the use of extra variables
int main()
{
	char csv[] = "Name,Age,Gender\nJohn,21,Male\nAnna,22,Female\nPatrick,30,Male";
	int i = 0;

	//declare and set the column and row count to zero first
	//colCount is already one because we are couting
	int colCount,rowCount, cellpadding;
	colCount = 1;
	rowCount = 0;
	cellpadding = 1;	

	//bool colCounted is declared to avoid counting if the number of first row is already counted
	bool colCounted = false;

	//find the number of rows and columns
	for (i = 0; i < strlen(csv); i++) {
		//count the columns
		//added condition to prevent counting more if comma is at the end of line
		if(csv[i] == ',' && csv[i+1] != '\n'){
			if(!colCounted)
				colCount++;

			//continue the count because comma(,) is not included			
			continue;	
		}

		//count the rows
		if(csv[i] == '\n' || i == strlen(csv) - 1) {
			rowCount++;
			//stop counting the columns because it is already counted
			colCounted = true;
		}
	}

	//find the longest number of characters per column

	//create the array to contain the longest lengths of columns
	int colspans[colCount];
	for(i=0; i<colCount; i++)
		colspans[i] = 0;
	
	int charCount = 0;
	int currentCol = 0;
	for(i=0; i<strlen(csv); i++) {
		//denotes that the end of a column is reached
		if(csv[i] == ',' || csv[i] == '\n') {
			colspans[currentCol] = (colspans[currentCol] < charCount) ? (charCount) : (colspans[currentCol]);	
			charCount = 0;
			currentCol = (csv[i] == '\n') ? 0 : ++currentCol;
			continue;
		}
		charCount++;
	}
	
	//find the longest line of a row
	int longestRow = 0;
	for(int i=0; i<colCount; i++) {
		longestRow += colspans[i];
	}

	//print the top border
	currentCol = 0;
	int indexAdded = 0;  
	for(i=0; i<=longestRow + cellpadding * 2 + colCount; i++) {
		if(i==0)
			printf(" +");
		if(i - indexAdded == colspans[currentCol] + cellpadding*2) {
			printf("+");
			indexAdded = i;
			currentCol++;
		}	
		printf("-");
	}
	printf("+\n");

	int printedChars = 0;
	int colIndex = 0;
	int j = 0;
	int rowIndex = 0;

	//print the data

	for(i=0; i<=strlen(csv); i++) {

		if(rowIndex == 1)
		{
			//print the top border
			currentCol = 0;
			int x = 0;
			int indexAdded = 0;  
			for(x=0; x<=longestRow + cellpadding * 2 + colCount; x++) {
				if(x==0)
					printf(" +");
				if(x - indexAdded == colspans[currentCol] + cellpadding*2) {
					printf("+");
					indexAdded = x;
					currentCol++;
				}	
				printf("-");
			}
			printf("+\n");
			rowIndex++;
		}

		if(csv[i] == '\n' || i == strlen(csv)) {
			for(j=printedChars; j<colspans[colIndex]; j++)
				printf(" ");
			printf(" |");
			printf("%c", csv[i]);

			colIndex = 0;
			printedChars = 0;
			rowIndex++;
			continue;

		}
		if(csv[i] == ',') {
			for(j=printedChars; j<colspans[colIndex]; j++)
				printf(" ");

			printf(" | ");
			colIndex++;
			printedChars = 0;
			continue;
		}
		if(csv[i-1] == '\n' || i == 0 || i == strlen(csv))
			printf(" | ");
		printf("%c", csv[i]);
		printedChars++;
	}
	printf("\n");
	
	//print the bottom border
	currentCol = 0;
	indexAdded = 0;  
	for(i=0; i<=longestRow + cellpadding * 2 + colCount; i++) {
		if(i==0)
			printf(" +");
		if(i - indexAdded == colspans[currentCol] + cellpadding*2) {
			printf("+");
			indexAdded = i;
			currentCol++;
		}	
		printf("-");
	}
	printf("+\n");
	return 0;
}
