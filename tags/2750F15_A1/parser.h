/**
 * parser.h:
 *
 * Variable and function definitions to be used for the parser.
 * Declares external variables for use in other functions.
 *
 * @author Neivin Mathew
 * @version 1.0, 2015/10/01
 * 
 */

#ifndef PARSER_H
#define PARSER_H

#include "common.h"

struct instr
{
	char label[26];
	char opcode[4];
	char am;
	char a[26];
	char bm;
	char b[26];
};

extern int instrCount;
extern char beginVal[25];

struct instr instructions[MAXINST];

/* --- Function declarations: parser.c --- */
int isLetter(char);

int isNumber(char);

void resetArray(char *, int);

void parser(char *);

#endif