API Description:

This code implements function to add and subtract roman numbers. The code is in src/ directory. The files are romanarithmetic.c
and romanarithmetic.h

int addRoman(char* num1, char* num2, char *result)

Function addRoman(..) adds two roman numbers specified by num1 and num2 and returns added number in result.
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


int subtractRoman(char* num1, char* num2, char *result)

Function subtractRoman(..) subtracts two roman numbers specified by num1 and num2 and returns added number in result.
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


Folder Description:
bin - folder holds executable for tests
bld - folder holds .o files during build
lib - folder holds .a files
src - holds .c and .h files
tst - holds tst.c and testcases.csv

testcases.csv file defines test vector. Each line holds a test case with each field seperated by a comma in following format

The test application, tst.exe, is obtained by compiling tst.c and linking with libkata.a ( roman arithmetic library from romanarithmetic.c ). It takes the name of testcases file as command line argument.

operation,first numeral, second numeral,expected result
example
+,I,I,II
-,II,I,I
-,I,I,
-,I,II,
For subtraction operation if second number is equal or greater than first then the result is empty string. See API description for more details.

How to build code:
makefile under kata folder is used to kickstart build. Below is description of different targets in the makefile
all: 
Target that builds both libkata ( library with roman arithmetic ) and test application
	
libkata:
Target to build just library (libkata) for roman arithmetic
			
test: 
Target is dependent upon libkata and builds test application.

runtest:
Target is dependent upon test: and will run the test application using test cases defined in testcases.csv

clean:
Removes .o and .exe files.
