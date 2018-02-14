#include <stdio.h>

/*
This program use 2 characters. Comparing them and testing their values program will decide to ignore (if the text is comment)
or not (in the case the text in source file is actual program code).

c:			character for getchar() input;
i:			integer for testing if we could compare previous character with the new character;
wait:			variable indicating how long to wait for flushing values from 'temp' and 's' if necessary;
empty:			test if the file is empty;
status_inline_comment:	status indicating if actual program is reading text from inline comment //;
status_comment:		status indicating if actual program is reading text from comment
			in_double_quotes:	status indicating if program inside double quotes "...". Multiplicating the value 
			of status by (-1). Initial value (-1), indicating outside. (1) indicating inside the double quotes.
			If program read inside double quotes no inside comments status are triggered.

temp:			the previous value of char;
s:			the actual value of char;
*/

int main()
{
	int c, i, wait, empty;
	int status_inline_comment, status_comment, in_double_quotes;
	char temp, s = EOF;	// initializing s to EOF in the case where is only one character in the source file
	
	i = wait = status_inline_comment = status_comment = 0;
	empty = 1;
	in_double_quotes = -1;
	
	/*	Thanks to "Salem" (from https://cboard.cprogramming.com)
		for the idea of getting first input into 'temp' variable and
		checking the case when there is only one character in the input file.
	*/
	if ((temp = getchar()) != EOF) empty = 0;
	while(((c = getchar()) != EOF) && empty == 0) {
		s = c;

		if (s == '/' && temp == '/' && in_double_quotes == -1 && status_comment == 0)
			status_inline_comment = 1;
		else if (status_inline_comment == 1 && s == '\n') {
			status_inline_comment = 0;
			wait = 1;
		}
		else if (s == '*' && temp == '/' && in_double_quotes == -1 && status_inline_comment == 0)
			status_comment = 1;
		else if (status_comment == 1 && s == '/' && temp == '*') { 
			status_comment = 0;
			wait = 2;
		}
		else if (temp != '\\' && s == '\"' && status_inline_comment == 0 && status_comment == 0)
			in_double_quotes = in_double_quotes * (-1);
		else;
		
		if (status_inline_comment == 0 && status_comment == 0) {
			if (wait == 0) putchar(temp);
			if (wait > 0) --wait;
		}	
		
		temp = s;
	}
	
	if (empty == 1) printf("File is empty.\n");	// 'printf' here only for testing purposes
	else if (s == EOF) putchar(temp);	// in the case if there is only one character in the source file
	
	printf("\nwhile((c = getchar()) != EOF) { /* input loop */");	// this line for the testing puposes
	
	return 0;
}
