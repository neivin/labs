/**
 * loader.c:
 *
 *	Functions to read in a binary .codemon file and package it a Codemon_pkg structure
 *	for submission to the Codex.
 * 
 * @author Neivin Mathew
 * @version 1.0, 2015/10/02
 * 
 */
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "arch.h"
#include "loader.h"

/**
 * verifyFilename:
 *
 * Returns 1 if file name is valid (has .codemon extension), and 0 otherwise.
 *
 * PRE: filename is a valid pointer to a file
 * POST: 1 if filename is valid, 0 otherwise
 */
int verifyFilename(char *filename){
	int len = strlen(filename);

	if(len < strlen(CODEMONEXT))
		return 0;
	if (filename == NULL)
		return 0;

	char *ext = strchr(filename, '.');
	if (strcmp(ext, CODEMONEXT) == 0)
		return 1;

	return 0;
}

/**
 * loader:
 *
 * Reads in a .codemon binary and packages it into a Codemon_pkg structure
 *
 * PRE: filename must be a valid pointer to a .codemon binary
 * POST: Codemon_pkg is created from the binary data in the .codemon file
 * 
 */
struct Codemon_pkg *loader(char *filename){
	
	struct Codemon_pkg *loadedMon = malloc(sizeof(struct Codemon_pkg));
	assert(loadedMon != NULL);

	int numLines = 0;
	
	uint32 beginVal; 	/* Store begin value from binary here */
	uint64 *code; 		/* Store instructions from binary here */

	/* If the input file has a invalid extension */
	if(verifyFilename(filename) == 0){
		printf("ERROR: Invalid name. Your Codemon file must be named: \"<your-name>.codemon\"\n");
		exit(1);
	}
	else {
		FILE *fp;

		fp = fopen(filename,"rb");
		if(!fp){
			printf("ERROR: Unable to open the file - \"%s.codemon\"\n", filename);
			exit(1);
		}

		/* Find the size of the file, to find the number of instructions */
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		numLines = (size - 4)/8;

		/* Allocate memory for reading in the instructions */
		code = malloc(sizeof(uint64)*numLines);

		/* Read in the begin value */
		fread(&beginVal,sizeof(uint32),1,fp);

		/* Read in all the instructions */
		fread(code,sizeof(uint64),numLines,fp);

		fclose(fp);
	}

	/* Remove the .codemon extension before packaging the name */
	int len = strlen(filename);
	filename[len - 8] = '\0';

	/* Package the values into the Codemon_pkg struct */
	strcpy(loadedMon->name, filename);
	loadedMon->lines = numLines;
	loadedMon->begin = beginVal;

	int i =0;
	for(i=0;i<numLines;i++){
		loadedMon->program[i] = code[i];
	}

	/* Free memory allocated while reading in instructions*/
	free (code);

	return loadedMon;
}


/* test code pls ignore
remove this main bruh

void main(){
	char *file = "1-Imp.codemon";
	//printf("filename verified: %d\n",verifyFilename(file));
	//printf("size of uint64 = %lu\n", sizeof(uint64));
	//loader(file);
	int reportid = runTest(loader(file), NULL, 0);
	printf("report ID = %d\n", reportid);
}
*/