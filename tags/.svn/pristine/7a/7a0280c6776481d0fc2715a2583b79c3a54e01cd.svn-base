/**
 * parser.c:
 *
 * Functions to parse raw text instructions into a instruction
 * structure, which can then be validated and used to generate
 * binary data.
 *
 * @author Neivin Mathew
 * @version 1.0, 2015/10/01
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> /* For memset() */
#include <ctype.h> /* For isspace() */
 
#include "common.h"
#include "parser.h"

/* Global external variables definitions */
int instrCount = 0;
char beginVal[25] = {'+'};
struct instr instructions[MAXINST];

/**
 * isLetter:
 * 
 * Returns 1 if the character ch is a capital letter, and 0 otherwise.
 *
 * PRE: ch is a valid ASCII character
 */
int isLetter(char ch){
	int c = (int) ch;
	if (c>=65 && c<=90)
		return 1;

	return 0;
}

/**
 * isNumber:
 * 
 * Returns 1 if the character ch is a number, and 0 otherwise.
 *
 * PRE: ch is a valid ASCII character
 */
int isNumber(char ch){
	int c = (int) ch;
	if (c>=48 && c<=57)
		return 1;

	return 0;
}

/**
 * resetArray:
 *
 * Fills an array of length size with the '+' character to 
 * denote that it is in a fresh/unmodified state.
 *
 * PRE: array != NULL, size > 0
 * POST: array is filled with '+'s
 */
void resetArray(char * array, int size){
	memset(array,'+',size);
}

/**
 * parser:
 *
 * Reads in a text file and parses it to a list of instructions according to
 * the Codemon specification.
 *
 * PRE: filename points to a file that follows the Codemon syntax.
 * POST: instructions[] is filled with parsed instructions from the file
 * 		 beginVal contains the begin value of the codemon program
 */
void parser(char *filename){
	FILE *fp;
	fp = fopen(filename,"r");
	
	/* If the file can be opened properly */
	if(fp == NULL){
		printf("ERROR: Can't open input file: %s\n", filename);
		exit(1);
	}

	/* Flags to keep track of instruction states */
	int hasBegin = 0;
	int hasLabel = 0;
	int hasOpcode = 0;
	int hasAMode =0;
	int hasA = 0;
	int hasBMode = 0;
	int hasB = 0;

	/* Comment mode flag */
	int isComment = 0;
	int inBegin = 0;

	/* Counter to store begin value */
	int begindex = 0;

	/* The character being read in */
	int c;
	char prevChar = '+';

	/* Temporary string to store data as it is read in */
	char tmp[25];
	resetArray(tmp,25);
	int tmpindex = 0;

	/* Read in characters till the end of the file */
	while((c = fgetc(fp)) != EOF){
		/* If the number of instruction exceeds the maximum allowed, terminate */
		if(instrCount>=MAXINST){
			printf("ERROR: The program has too many instructions.\n");
			exit(1);
		}

		/* Check if lowerase, convert to uppercase and then cast to char */
		if(c >= 97 && c <= 122)
			c-= 32;
		char ch = (char) c;

		/* If currently in a comment:
		 *		1) If you encounter a newline char, terminate comment & read next char
		 *		2) Otherwise ignore char */
		if (isComment == 1){
			if (ch == '\n'){
				isComment = 0;
				continue;
			}
			else
				continue;
		}

		/* Check for the start of a comment */
		if (ch == '!'){
			isComment = 1;
			continue;
		}

		/* Look for the begin statement */
		if (hasBegin == 0){
			/* Mark flag hasBegin at the end of the begin instruction */
			if (ch == ';' && inBegin == 1){
				inBegin = 0;
				hasBegin = 1;
			}
			if(isLetter(prevChar) || prevChar == '+'){
				// Update prevChar and read next char
			}
			/* Recognize that you are reading the begin value */
			if(ch == '@'){
				inBegin = 1;
			}
			else if(prevChar == '@' || inBegin == 1){ /* Update the beginVal */
				beginVal[begindex] = ch;
				begindex++;
			}

		}
		/* Read in instructions once you have the begin statement */
		else {
			// If you just read in a label or field or mode, don't include the
			// special chars in the tmp buffer
			if (prevChar == ':' || prevChar == ';'|| prevChar == ',' || prevChar == '$' || 
			prevChar == '#' || prevChar == '[' || prevChar == '*' || 
			prevChar == '{' || prevChar == '}' || prevChar == ']' || 
			prevChar == '@' || prevChar == '<' ||prevChar == '>'){
				
				tmpindex = 0;
				resetArray(tmp,25);
			}
			/* If reading in a label */
			if (ch == ':' && hasLabel == 0 && hasOpcode == 0){
				hasLabel = 1;	

				tmp[tmpindex] = '\0';
				strcpy(instructions[instrCount].label, tmp);

				tmpindex = 0;
				resetArray(tmp,25);
			}
			/* If you have just read in an OPCODE */
			else if(hasOpcode == 0 && ch == ' ' && isLetter(prevChar)){
				
				hasOpcode = 1;
				tmp[tmpindex] = '\0';
				strcpy(instructions[instrCount].opcode, tmp);

				tmpindex=0;
				resetArray(tmp,25);
			}
			/* Catch the instructions where OPCODES need no fields */
			else if (ch == ';' && hasOpcode == 0 && hasA == 0 && hasB == 0 ){
				hasOpcode = 1;
				tmp[tmpindex] = '\0';
				strcpy(instructions[instrCount].opcode, tmp);

				tmpindex=0;
				resetArray(tmp,25);
			}
			/* By default put a single field instruction into the A-field */
			else if((ch == ',' || ch == ';') && hasA == 0 && hasOpcode == 1){
				/* If no addressing mode read, assign it direct mode */
				if(hasAMode == 0){
					instructions[instrCount].am = '$';
					hasAMode = 1;
				}

				hasA = 1;
				tmp[tmpindex] = '\0';
				strcpy(instructions[instrCount].a, tmp);
				
				tmpindex=0;
				resetArray(tmp,25);
			}
			/* If you have just read in the B field */
			else if (ch == ';' && hasA == 1 && hasB == 0 && hasOpcode == 1){
				if(hasBMode == 0){
					instructions[instrCount].bm = '$';
					hasBMode = 1;
				}

				tmp[tmpindex] = '\0';
				strcpy(instructions[instrCount].b, tmp);

				tmpindex=0;
				resetArray(tmp,25);

			}
			/* Assign addressing modes */
			/* Assign B-field mode first to prevent overwriting by A-mode */
			if(hasBMode == 0 && hasAMode == 1){
				if (ch == '$' || ch== '#' || ch == ']' || ch == '@' || ch == '<' || ch == '>'){
					hasBMode = 1;
					instructions[instrCount].bm = ch;
				}
			}

			if(hasAMode == 0){
				if (ch == '$' || ch== '#' || ch == '[' || ch == '*' || ch == '{' || ch == '}'){
					hasAMode = 1;
					instructions[instrCount].am = ch;
				}
			}

			/* Once you reach the end of the instruction,
			   store values, reset flags and buffer, and increment instr count */
			if(ch == ';'){
				instrCount++;

				hasLabel = 0;
				hasOpcode = 0;
				hasAMode =0;
				hasA = 0;
				hasBMode = 0;
				hasB = 0;

				tmpindex=0;
				resetArray(tmp,25);	
			}

			/* If the character is not a space, put it in the temporary buffer */
			if (!isspace(c)){
				tmp[tmpindex] = ch;
				tmpindex++;
			}

		} /* End of else (after begin) */
		
		/* If whitespace, skip char and don't put record it as the previous character */
		if (isspace(c)){
			continue;
		}

		prevChar = ch;
	} /* end of while (y'all got any more of them characters) */
	
	/* Trim OPCODEs to 3 characters */
	/* Probably not needed */
	int i;
	for (i=0;i<instrCount;i++){
		instructions[i].opcode[3] = '\0';
	}

	/* Close the file */
	fclose(fp);
}/* end of parser() */