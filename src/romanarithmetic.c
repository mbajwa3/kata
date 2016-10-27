#include <stdio.h>
#include <string.h>
#include "romanarithmetic.h"

/*Return status definition for static functions*/
#define RETURN_SUCCESS 1
#define RETURN_FAILURE 0

/* Constant definitions for roman numerals and loop up tables derived from rule set */
#define NUMBER_OF_ROMAN_NUMERALS 7
const char* romanNumeralsSet = "IVXLCDM";

#define SHORT_FORM_LENGTH 3
#define LONG_FORM_LENGTH 6

#define EQUIVALENCE_TABLE_SIZE 12
#define LENGTH_MULTIPLIER 5

/*struct that hold equvialent expanded forms for roman numerals*/
typedef struct {
	char shortForm[SHORT_FORM_LENGTH];
	char expandedForm[LONG_FORM_LENGTH];
} equivalence;


const equivalence equivalenceTable[EQUIVALENCE_TABLE_SIZE] = {{"IV", "IIII"}, {"V", "IIIII"}, {"IX", "VIIII"}, {"X", "VV"}, {"XL", "XXXX"}, {"L", "XXXXX"}, {"XC", "LXXXX"}, {"C", "LL"}, {"CD", "CCCC"}, {"D", "CCCCC"}, {"CM", "DCCCC"}, {"M", "DD"} };

/* Function ClearBuffer(..) clears a passed input buffer

Arguments:

buffer - pointer to buffer to be cleared
size - size of buffer to be cleared

*/

static void clearBuffer(char *buffer, int size)
{
	memset(buffer,'\0',size);
}

/* Function getOrderOfNumeral(..) returns index of numeral in romanNumeralsSet[]. Higher index means higer order numeral

Arguments:

ch - passed in numeral whose order is to be found

Return value :
-1 if passed in char ch is not in romanNumeralsSet[]
index of char ch if it is in romanNumeralsSet[]

*/

static int getOrderOfNumeral(char ch)
{
	char *chPosition = strchr(romanNumeralsSet, ch);
	
	if(chPosition == NULL)
	{
		return -1;
	}
	else
	{
		return ((chPosition - romanNumeralsSet)/sizeof(ch));
	}
	
}

/* Function getEquivalent(..) gets teh equivalent string from equivalenceTable[].

Arguments:

inString - pointer to the string whose equivalent string is to be found
outString - holds the string found from equivalenceTable[]
base - it defines if the passed in string is in short form or expanded form

0 - passed in string is in short form and expanded form of string will be returned
1 - passed in string is in expanded form and short form of string will be returned

Return value:
RETURN_SUCCESS  - if inString was in equivalenceTable[]
RETURN_FAILURE - if inString was not in equivalenceTable[]

*/


static int getEquivalent(char *inString, char *outString, int base)
{
	char *basePtr;
	int i;
	/* base == 0 short form is passed, need expanded form */
	if(base == 0)
	{
		for( i = 0; i < EQUIVALENCE_TABLE_SIZE; i++ )
		{
			if( strcmp(inString, equivalenceTable[i].shortForm) == 0)
			{
				clearBuffer(outString, strlen(equivalenceTable[i].expandedForm));
				strcpy(outString, equivalenceTable[i].expandedForm);
				return RETURN_SUCCESS;
			}			
		}
	}
	else
	{
		for( i = 0; i < EQUIVALENCE_TABLE_SIZE; i++ )
		{
			if( strcmp(inString, equivalenceTable[i].expandedForm) == 0)
			{
				clearBuffer(outString, strlen(equivalenceTable[i].shortForm));
				strcpy(outString, equivalenceTable[i].shortForm);
				return RETURN_SUCCESS;
			}			
		}
	}
	
	return RETURN_FAILURE;
}

/* Function checkValidNumeral(..) checks in passed in numeral is in romanNumeralsSet[]

Arguments:

num - numeral to checked if it is valid

Return value:
INVALID_INPUT  - if num was in romanNumeralsSet
NO_ERROR - if num was not in romanNumeralsSet

*/

static int checkValidNumeral(char* num)
{
	
	
	int count = strspn (num, romanNumeralsSet);
		
	if(count != strlen(num))
	{
		return INVALID_INPUT;
	}
	
	return NO_ERROR;
	
}

/* Function checkValidInputs(..) checks if passed in arguments are

1. Not NULL
2. Made of string with valid roman numerals
3. Does not exceed the maximum expected length.

Arguments:

num1 - pointer to  first numeral string for the arithmetic operation
num1 - pointer to  second numeral string for the arithmetic operation
result - pointer to hold the result of arithmetic operation

Return value:
NO_ERROR  - if all three arguments passed (10 (2) and (3) above
NULL_PTR_PASSED - if one of passed in argument is null
INPUT_OUT_OF_RANGE - if num1 or num2 exceeds maximum expected length
INVALID_INPUT - if string is made of characters not in romanNumeralsSet[]

*/
static int checkValidInputs(char* num1, char* num2, char *result)
{
	/* Check for null ptrs */
	if( (num1 == NULL) || (num2 == NULL) || (result == NULL) )
	{
		printf("Null pointer passed as an argument\n");
		return NULL_PTR_PASSED;
	}
	
	/* Check if the length of input strings is valid */
	if( (strlen(num1) > MAX_LENGTH_INPUT_NUMERALS) || (strlen(num2) > MAX_LENGTH_INPUT_NUMERALS) )
	{
		printf("Input value out of range\n");
		return INPUT_OUT_OF_RANGE;
	}
	
	if(checkValidNumeral(num1) == NO_ERROR)
	{
		if( checkValidNumeral(num2) == INVALID_INPUT )
		{
			printf("Invalid second input %s\n", num2);
			return INVALID_INPUT;
		}
	}
	else 
	{
			printf("Invalid first input %s\n", num1);
			return INVALID_INPUT;
	}
	
	return NO_ERROR;	
}

/* Function expandNumeralForSubtractive(..) expands the subtractives ( two character number with lesser number on left) to equivalent string from equivalenceTable[]

Arguments:

inString - pointer to numeral string whose subtractives need to be expanded
outString - pointer to hold the expanded string.

Return value:
None

*/

static void expandNumeralForSubtractive(char *inString, char *outString)
{
	int inLen = strlen(inString);
	char finalString[inLen * LENGTH_MULTIPLIER + 1];
	char compactString[SHORT_FORM_LENGTH];
	char expandedString[LONG_FORM_LENGTH];
	int i;
	int finalStringIndex;

	if( inLen == 1 )
	{
		clearBuffer(outString,inLen);
		strcpy(outString, inString);
		return;
	}
	
	clearBuffer(finalString,inLen * LENGTH_MULTIPLIER + 1);
	compactString[2] = '\0';
	finalStringIndex = 0;

	for( i=0; i < inLen; )
	{
	  compactString[0] = inString[i];
	  compactString[1] = inString[i+1];
	  clearBuffer(expandedString,LONG_FORM_LENGTH);
	  if( getEquivalent(compactString,expandedString,0) == RETURN_FAILURE )
	  {
		finalString[finalStringIndex] = inString[i];
		i++;
		finalStringIndex++;
	  }
	  else
	  {
		strcpy(&finalString[finalStringIndex], expandedString);
		i += 2;
		finalStringIndex += strlen(expandedString);
	  }
	  
	  if( i == (inLen-1) )
	  {
		finalString[finalStringIndex] = inString[i];
		finalStringIndex++;
		i++;
	  }
	  
	}
	
	clearBuffer(outString,finalStringIndex);
	strcpy(outString, finalString);
	return;
		
}

/* Function combineAndSort(..) combines two input string and merges them with highest order numeral on the left. Uses merge sort algorithm.

Arguments:

inString1 - pointer to first string that is to be merged
inString2 - pointer to second string that is to be merged
outString - pointer to hold the merged and sorted string.

Return value:
None

*/

static void combineAndSort(char* inString1, char* inString2, char *outString)
{
		int indexString1 = 0;
		int indexString2 = 0;
		int indexOutString;
		
		int lenString1 = strlen(inString1);
		int lenString2 = strlen(inString2);
		int lenOutString = lenString1 + lenString2;
		
		clearBuffer(outString,lenOutString);
		
		for(indexOutString = 0; indexOutString < lenOutString; indexOutString++)
		{
		
			if( (indexString1 < lenString1) && (indexString2 < lenString2) )
			{
				if(getOrderOfNumeral(inString1[indexString1]) > getOrderOfNumeral(inString2[indexString2]) )
				{
					outString[indexOutString] = inString1[indexString1];
					indexString1++;
				}
				else
				{
					outString[indexOutString] = inString2[indexString2];
					indexString2++;
				}
			}
			else if( (indexString1 == lenString1) && (indexString2 < lenString2) )
			{
				strcat(outString, &inString2[indexString2]);
				break;
			}
			else if( (indexString2 == lenString2) && (indexString1 < lenString1) )
			{
				strcat(outString, &inString1[indexString1]);
				break;
			}
			else
			{
				break;
			}
			
		}
}

/* Function findAndReplacePattern(..) replaces a pattern with equivalent short form string from equivalenceTable[]. Uses sliding window technique starting from end of string towards beginning.

Arguments:

inputString - pointer to string whose pattern would be replaced
outputString - pointer to string to hold output string
mode - used to specify if replacement is to done using single char or double char ( subtractives) numerals.

Return value:
0 - if no pattern found and replacement done
1 - if a pattern was found and replacement was done

*/

static int findAndReplacePattern(char* inputString, char* outputString, int mode)
{
	int i;
	char *endPtr;
	char *beginPtr;
	char* searchedStringLocation;
	int len;
	int inLen = strlen(inputString);
	char tempStr[inLen+1];
	int expLen;
	int subStrLen;
	int index;

	endPtr = &inputString[inLen-1];
	
	if(inLen == 1)
	{
		strcpy(outputString,inputString);
		return 0;
	}
	
	endPtr = &inputString[inLen-1];
	while(1)
	{
		subStrLen = 0;
		beginPtr = endPtr;
		while(1)
		{
			
			if(*beginPtr == *endPtr)
			{
				subStrLen++;
			}
			else
			{
				if(mode == 1)
				{
					beginPtr++;
				}
				break;
			}
			if(beginPtr == inputString)
			{
				break;
			}
			beginPtr--;
		}
		
		if(subStrLen > 1)
		{
			clearBuffer(tempStr,inLen+1);
			if(mode == 1)
			{
				strncpy(tempStr,beginPtr,subStrLen);
			}
			else
			{
				strncpy(tempStr,beginPtr,subStrLen+1);
			}
				
			for( i = 0; i < EQUIVALENCE_TABLE_SIZE; i++ )
			{
				if(mode == 1)
				{
					index = i;				
				}
				else
				{
					index = EQUIVALENCE_TABLE_SIZE - 1 - i;
				}
				if(strlen(equivalenceTable[index].shortForm) == mode)
				{
					searchedStringLocation = strstr(tempStr, equivalenceTable[index].expandedForm);
	
					if(searchedStringLocation != NULL)
					{
						//start constructing output string
						len = (beginPtr - inputString)/sizeof(char);
						strncpy(outputString, inputString, len);
						strncat(outputString,tempStr,(searchedStringLocation-tempStr));
						strcat(outputString, equivalenceTable[index].shortForm);
						strcat(outputString,searchedStringLocation+strlen( equivalenceTable[index].expandedForm));
						strcat(outputString, beginPtr+strlen(tempStr));
						return 1;
					}
				}
			}
		}
		
		if(endPtr == inputString)
		{
			break;
		}
		
		endPtr--;
		
	}	
	
	return 0;
}

/*
static int findAndReplacePattern(char* inputString, char* outputString, int mode)
{
	int i;
	char* searchedStringLocation;
	int len;
	
	for( i = 0; i < EQUIVALENCE_TABLE_SIZE; i++ )
	{
		if(strlen(equivalenceTable[i].shortForm) == mode)
		{
			searchedStringLocation = strstr(inputString, equivalenceTable[i].expandedForm);
			if(searchedStringLocation != NULL)
			{
				//start constructing output string
				len = (searchedStringLocation - inputString)/sizeof(char);
				strncpy(outputString, inputString, len);
				strcat(outputString, equivalenceTable[i].shortForm);
				strcat(outputString, &searchedStringLocation[strlen(equivalenceTable[i].expandedForm)]);
				return 1;
			}
		}
	}
	return 0;
}*/

/* Function compactStrings(..) takes inputString and compacts it by replacing longer patterns with shorter forms from equivalenceTable[]

Arguments:

inputString - pointer to string which is to be compacted
outputString - pointer to string to hold output compacted string

Return value:
None
*/

static void compactStrings(char* inputString, char* outputString)
{
	int inLen = strlen(inputString);
	
	if(inLen == 0)
		return ;
	
	/* Locate 2 or 5 char length patterns from expanded form in table and replace with single char */
	while(findAndReplacePattern(inputString,outputString,1))
	{
		strcpy(inputString,outputString);
		clearBuffer(outputString,strlen(outputString));
	}
	while(findAndReplacePattern(inputString,outputString,2))
	{
		strcpy(inputString,outputString);
		clearBuffer(outputString,strlen(outputString));
	}
	
}

/* Function removeCommonSymbolsFromMinuend(..) crosses out common numerals between minuend and subtrahend

Arguments:

minuend - pointer to string which holds minuend
subtrahend - pointer to string to holds subtrahend

Return value:
None
*/

static void removeCommonSymbolsFromMinuend(char *minuend, char *subtrahend)
{
	int i;
	char *posPtr;
	
	for(i = 0; i < strlen(subtrahend); i++)
	{
		posPtr = strchr(minuend,subtrahend[i]);
		if( posPtr != NULL )
		{
			*posPtr = '\0';
			posPtr++;
			strcat(minuend,posPtr);
			subtrahend[i] = '\0';
			strcat(subtrahend, &subtrahend[i+1]);
			i--;
		}
	}
	
}

/* Function expandForSpecifiedNumeral(..) replaces aa numeral in inString with expanded form so that the string with  specified numeral is obtained. Used for getting symbols that are in subtrahend so that they can be crossed out.

Arguments:

inString - pointer to string in which numeral to be expanded
numeral - numeral for which a higher order numeral is to be expanded to get a string with specified numeral

Return value:
None
*/

static void expandForSpecifiedNumeral(char *inString, char numeral)
{
	int i;
	int orderOfIncomingNumeral;
	int orderOfNexAvaialableNumeralInstring;
	char *posPtr;
	int inLen = strlen(inString);
	char tempStr[inLen];
	char expandedForm[LONG_FORM_LENGTH];
	char numStr[2];
	
	orderOfIncomingNumeral = getOrderOfNumeral(numeral);
	clearBuffer(tempStr,inLen);
	
	for(i = orderOfIncomingNumeral+1; i < NUMBER_OF_ROMAN_NUMERALS; i++)
	{
		posPtr = strrchr(inString,romanNumeralsSet[i]);
		if(posPtr != NULL)
		{
			*posPtr = '\0';
			*posPtr++;
			strcpy(tempStr,posPtr);
			clearBuffer(expandedForm,LONG_FORM_LENGTH);
			numStr[0] = romanNumeralsSet[i];
			numStr[1] = '\0';
			getEquivalent(numStr,expandedForm,0);
			strcat(inString,expandedForm);
			strcat(inString,tempStr);
			if( (i - orderOfIncomingNumeral) == 1 )
			{
				break;
			}
			i = i-2;
		}
	}
}

/* Function addRoman(..) adds two roman numbers specified by num1 and num2 and returns added number in result.

The algorithm steps are below after checking for validity of inputs

1. Expand num1 and num2 to replace subtractives ( two string number with a lesser numeral on left) with equivalent strings specified in equivalenceTable[]
2. Combine the two strings from (1) and sort them with highest number on left
3. Compact the string obtained from (2) with equivalent shorter forms in equivalenceTable[]
4.  Copy string from (3) to result string.
5. Result string should be evaluated in conjunction with return value
6. if funciton return error value, result will be null


Arguments:

num1 - pointer to first roman number
num2 - pointr to second roman number
result - pointer to hold output result.

Return value:
NO_ERROR   - Addition was successful, output in result string

INVALID_INPUT 	- One of passed in Input was invalid ( that is string has characters not in roman numeral set)
NULL_PTR_PASSED - One of argument was null
INPUT_OUT_OF_RANGE - Input string too long
OUTPUT_OUT_OF_RANGE  - calculated output out of range

*/

int addRoman(char* num1, char* num2, char *result)
{
	
	int num1Len = strlen(num1) * LENGTH_MULTIPLIER;
	int num2Len = strlen(num2) * LENGTH_MULTIPLIER;
	int expandedLen = num1Len + num2Len;
	char expandedNum1[num1Len];
	char expandedNum2[num2Len];
	char expandedCombindedString[expandedLen];
	char compactString[expandedLen];

	clearBuffer(result,expandedLen);	
	int returnValue = checkValidInputs(num1,num2,result);
	if( returnValue < 0)
	{
		return returnValue;
	}
	
	/*Expand incoming numerals for numbers on left*/
	expandNumeralForSubtractive(num1, expandedNum1);
	expandNumeralForSubtractive(num2, expandedNum2);
	
	/*Combine  and sort the expanded strings to get Combinded string */
	clearBuffer(expandedCombindedString,expandedLen);
	clearBuffer(compactString,expandedLen);
	combineAndSort(expandedNum1,expandedNum2,expandedCombindedString);
	compactStrings(expandedCombindedString,compactString);
	clearBuffer(result,strlen(expandedCombindedString));
	strcpy(result,expandedCombindedString);
	printf("%s + %s = %s\n", num1, num2, result);
	
	return NO_ERROR;
}

/* Function subtractRoman(..) subtracts two roman numbers specified by num1 and num2 and returns added number in result.

The algorithm steps are below after checking for validity of inputs

1. Expand num1( minuend )  and num2 ( subtrahend) to replace subtractives ( two string number with a lesser numeral on left) with equivalent strings specified in equivalenceTable[]
2. Cross out symbols from num1 that are in num2, expand num1 symbols to expanded form from equivalenceTable[], untill all the symbols from num2 are crossed out from num1
3. Compact the string obtained from (2) with equivalent shorter forms in equivalenceTable[]
4.  Copy string from (3) to result string.
5. Result string should be evaluated in conjunction with return value
6. If two strings are equal a null string will be returned in result
7. if funciton return error value, result will be null


Arguments:

num1 - pointer to first roman number
num2 - pointr to second roman number
result - pointer to hold output result.

Return value:
NO_ERROR   - Addition was successful, output in result string

INVALID_INPUT 	- One of passed in Input was invalid ( that is string has characters not in roman numeral set)
NULL_PTR_PASSED - One of argument was null
INPUT_OUT_OF_RANGE - Input string too long
OUTPUT_OUT_OF_RANGE  - calculated output out of range
SUBTRAHEND_GREATER_MINUEND - Subtrahend is greater than minuend
*/


int subtractRoman(char* num1, char* num2, char *result)
{
	
	int num1Len = strlen(num1) * LENGTH_MULTIPLIER;
	int num2Len = strlen(num2) * LENGTH_MULTIPLIER;
	int expandedLen = num1Len + num2Len;
	char expandedNum1[num1Len];
	char expandedNum2[num2Len];
	char compactString[expandedLen];

	clearBuffer(result,expandedLen); 
	int returnValue = checkValidInputs(num1,num2,result);
	
	if( returnValue < 0)
	{
		return returnValue;
	}
	
	/*Check if Subtrahend is greater than minuend*/
	if(getOrderOfNumeral(num1[0]) < getOrderOfNumeral(num2[0]) )
	{
		printf("Subtrahend greater than minuend\n");
		return SUBTRAHEND_GREATER_MINUEND;
	}
	
	/*Expand incoming numerals for numbers on left*/
	clearBuffer(expandedNum1,num1Len);
	clearBuffer(expandedNum2,num2Len);
	expandNumeralForSubtractive(num1, expandedNum1);
	expandNumeralForSubtractive(num2, expandedNum2);
	while(1)
	{
		removeCommonSymbolsFromMinuend(expandedNum1, expandedNum2);
	
		int strLen1 = strlen(expandedNum1);
		int strLen2 = strlen(expandedNum2);
	
		if((strLen1 > 0) && (strLen2 == 0))
		{
			clearBuffer(result,strLen1);
			strcpy(result,expandedNum1);
			break;
		}
		else if( (strLen1 == 0) && (strLen2 > 0))
		{
			printf("Subtrahend greater than minuend2\n");
			return SUBTRAHEND_GREATER_MINUEND;
		}
		else if( (strLen1 == 0) && (strLen2 == 0))
		{
			printf("Subtrahend equal minuend\n");
			break; 
		}
		else
		{
			expandForSpecifiedNumeral(expandedNum1,expandedNum2[strLen2-1]);
		}
	}

	clearBuffer(compactString,expandedLen);
	compactStrings(expandedNum1,compactString);
	clearBuffer(result,strlen(expandedNum1));
	strcpy(result,expandedNum1);
	printf("%s - %s = %s\n", num1, num2, result);
	return NO_ERROR;
	
}