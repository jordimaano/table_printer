#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//still needs improvement
//needs to create separate functions for repetitive actions
//reduce cases (if/else)
//reduce the use of extra variables
void printBorder(int[], int, int, int);

bool checkQuotation(char[], int);
FILE *fptr;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please specify a file to process.\n");
		printf("Usage: %s <filename>", argv[0]);
		return 1;
	}
	const char *filename = argv[1];
	fptr = fopen(filename, "r"); 
	char csv[1000];
	if(fptr==NULL){
		printf("Unable to open file.");
		return 0;
	}

	int i = 0;

	//declare and set the column and row count to zero first
	//colCount is already one because we are couting
	int colCount,rowCount, cellpadding;
	colCount = 1;
	rowCount = 0;
	cellpadding = 1;	


	//count rows;
	while(fgets(csv,100,fptr)) {
		rowCount++;
	}

	bool insideQuotation = false;
	for(i=0; i<strlen(csv); i++)
	{
		//check if the comma is not inside quotations 
		if(csv[i] == '"' && checkQuotation(csv, i))
			insideQuotation = !insideQuotation;

		if(csv[i] == ',' && insideQuotation == false) 
			colCount++;
	}


	//find the longest number of characters per column

	//create the array to contain the longest lengths of columns
	int colspans[colCount];
	for(i=0; i<colCount; i++)
		colspans[i] = 0;
	
	int charCount = 0;
	int currentCol = 0;
	insideQuotation = false;

	rewind(fptr);
	//count the longest character for each column
	while (fgets(csv, 100, fptr)) {
		currentCol = 0;
		for(i=0; i<strlen(csv); i++) {
			//ignore quotation marks
			if(csv[i] == '"' && checkQuotation(csv, i)) {
				insideQuotation = !insideQuotation;
				continue;
			}

			//denotes that the end of a column is reached
			if((csv[i] == ',' && insideQuotation == false) || csv[i] == '\n') {
				colspans[currentCol] = (colspans[currentCol] < charCount) ? (charCount) : (colspans[currentCol]);	
				charCount = 0;
				currentCol++;
				continue;
			}
			charCount++;
		}
	}
		
	//find the longest line of a row
	int longestRow = 0;
	for(int i=0; i<colCount; i++) {
		longestRow += colspans[i];
	}

	//print the top border
	printBorder(colspans, cellpadding, colCount, longestRow);

	int printedChars = 0;
	int colIndex = 0;
	int j = 0;
	int rowIndex = 0;

	//print the data


	insideQuotation = false;
	rewind(fptr);
	while(fgets(csv, 100, fptr)) {
		if(rowIndex == 1) {
			printBorder(colspans, cellpadding, colCount, longestRow);
		}
		printedChars = 0;
		colIndex = 0;
		printf(" | ");
		for(i=0; i<strlen(csv); i++) {
		//ignore quotation marks when printing
			if(csv[i] == '"' && checkQuotation(csv, i)) {
				insideQuotation = !insideQuotation;
				continue;
			}
			if(csv[i] == ',' && !insideQuotation) { 

				if (csv[i+1] != '\n') {
					for(j=printedChars; j<colspans[colIndex]; j++)
						printf(" ");
					printedChars = 0;	
					colIndex++;
					printf(" | ");
				}
				continue;
			}
			if(csv[i] == '\n')
				continue;
			printf("%c", csv[i]);
			printedChars++;
		}
			for(j=printedChars; j<colspans[colIndex]; j++)
				printf(" ");
			printedChars = 0;	
			colIndex++;
		printf(" |");
		printf("\n");
		rowIndex++;
	}


	
	//print the bottom border
	printBorder(colspans, cellpadding, colCount, longestRow);
	fclose(fptr); 

	//for testing 
	/*
	printf("\nRowLength: %d", longestRow);

	printf("\n");

	for(i=0; i<colCount; i++)
	{
		printf("%d\n", colspans[i]);
	}
	*/

	return 0;
}

void printBorder(int colspans[], int cellpadding, int colCount, int rowLength)
{
	//print the top border
	int currentCol = 0;
	int indexAdded = 0;  
	int i;
	for(i=0; i<rowLength + cellpadding * 2 * colCount; i++) {
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
}

//should return true if quotation is valid (e.g. right before/after comma/newline) 
bool checkQuotation(char csv[], int i)
{
	if(csv[i+1] == ',' || csv[i+1] == '\n')
		return true;
	if(csv[i-1] == ',' || csv[i+1] == '\n')
		return true;

	return false;
}

