#ifndef ROMAN_ARITHMETIC_H
#define ROMAN_ARITHMETIC_H

/*Return value definition */

#define NO_ERROR  1

#define INVALID_INPUT 			-1
#define NULL_PTR_PASSED 		-2
#define INPUT_OUT_OF_RANGE 		-3
#define OUTPUT_OUT_OF_RANGE 	-4
#define SUBTRAHEND_GREATER_MINUEND -5

/*Limits for length of numerals */

#define MAX_LENGTH_INPUT_NUMERALS 256
#define MAX_LENGTH_OUTPUT_NUMERALS 2 * 256

/* Function addRoman(..) adds two roman numbers specified by num1 and num2 and returns added number in result.
Result string should be evaluated in conjunction with return value.
if funciton return error value, result will be null.

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

int addRoman(char* num1, char* num2, char *result);

/* Function subtractRoman(..) subtracts two roman numbers specified by num1 and num2 and returns added number in result.
Result string should be evaluated in conjunction with return value.
if funciton return error value, result will be null.

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


int subtractRoman(char* num1, char* num2, char *result);

#endif // ROMAN_ARITHMETIC_H