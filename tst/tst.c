#include <stdio.h>
#include <string.h>

/*Data Structures */

/* Defines for test case file */

#define  TEST_CASE_FILE_DELIMITER ","

#define TEST_LINE_LENGTH (int)256
#define NUMBER_OF_TOKENS (unsigned short)4

#define OPERATION_POS  (unsigned short)0
#define NUMERAL_1_POS  (unsigned short)1
#define NUMERAL_2_POS  (unsigned short)2
#define RESULT_POS	   (unsigned short)3

/*Function clearBuffer: Function to clear buffer with number of bytes equal to size */
void clearBuffer(char *buffer, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		buffer[i] = '\0';
	}
}

int main(int argc, char **argv)
{
	/* Test case File Pointer */
	FILE *tstCaseFP;
	
	/*Parameters used to read from test case file */
	char testBuffer[TEST_LINE_LENGTH];
		
	/* Pointers to hold test values from test case file */
	char testVector[NUMBER_OF_TOKENS][TEST_LINE_LENGTH];
	
	/* Buffer for holding calculaed results */
	char calculatedResult[TEST_LINE_LENGTH];

	/*Check if right number of arguments were passed to program */
	if(argc != 2)
	{
		printf("Usage is: tst.exe <test case filename> \n");
		return -1;
	}

	 /* Open test case file and read test vectors from it */
	tstCaseFP = fopen(argv[1],"r");
	
	if(tstCaseFP == NULL)
	{
		printf("Cannot open test case file %s\n", argv[1]);
		return -1;
	}
	
	int lineNumber = 0;
	while(fgets(testBuffer, TEST_LINE_LENGTH, tstCaseFP) != NULL)
	{
		//printf("%s",testBuffer);
		lineNumber++;
		/*Check to see if it is first line describing file format*/
		if(testBuffer[0] == '#')
		{
			continue;
		}
				
		/*Break test file line into test vector*/
		unsigned short i = 0;
		char *token = strtok(testBuffer,TEST_CASE_FILE_DELIMITER);
		while(token != NULL && i < NUMBER_OF_TOKENS)
		{
			strcpy(testVector[i],token);
			if(testVector[i][strlen(token)-1] == '\n')
			{
				testVector[i][strlen(token)-1] = '\0';
			}
			i++;
			token = strtok(NULL,TEST_CASE_FILE_DELIMITER);
		}
		if(strcmp(testVector[OPERATION_POS], "+") == 0)
		{
			addRoman(testVector[NUMERAL_1_POS],testVector[NUMERAL_2_POS],calculatedResult);
		}
		else if(strcmp(testVector[OPERATION_POS], "-") == 0)
		{
			subtractRoman(testVector[NUMERAL_1_POS],testVector[NUMERAL_2_POS],calculatedResult);
		}
		else
		{
			printf("Invalid operation %s specified in test case line number %d\n", testVector[OPERATION_POS],lineNumber);
		}

		if(strcmp(calculatedResult,testVector[RESULT_POS]) == 0)
		{
			printf("Test line number %d passed\n", lineNumber);
		}
		else
		{
			printf("Test line number %d failed\n", lineNumber);
		}
		
		clearBuffer(testBuffer, TEST_LINE_LENGTH);
		clearBuffer(calculatedResult, TEST_LINE_LENGTH);		
	}
	
	/*Close test case file*/
	fclose(tstCaseFP);
	
	return 1;
}