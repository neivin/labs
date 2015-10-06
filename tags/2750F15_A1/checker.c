/**
 * checker.c:
 *
 *	Functions to ensure that the codemon program that was read in is valid.
 *	The subroutines resolve all the labels in the program, and enforce constraints
 *	on various instructions.
 * 
 * @author Neivin Mathew
 * @version 1.0, 2015/10/02
 * 
 */
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parser.h"
#include "checker.h"

char labels[MAXINST][26];
char label_pos[MAXINST];

/**
 * resolveLabels:
 *
 * Removes all labels from the codemon instruction array and from the begin value.
 *
 * PRE: instructions[] must contain parsed instructions from the codemon program
 * 		beginVal must contain a label/value present in the codemon program
 * POST: All labels in instructions[] are replaced with the corresponding numerica value
 * 
 */
int resolveLabels(){
	int i,j;
	int diff = 0;
	int labelCount = 0;

	for(i=0;i<instrCount;i++){
		/* If an instruction has a label:
		 * 		1) Add it to the label list 
		 * 		2) Record its position */
		if(instructions[i].label[0] != '\0'){
			strcpy(labels[labelCount],instructions[i].label);
			label_pos[labelCount] = i;
			labelCount++;
		}
	}

	/* Resolve begin value label if it has one */
	for(i=0;i<labelCount;i++){
		if(strcmp(labels[i],beginVal) == 0){
			diff = label_pos[i] - 0;
			sprintf(beginVal,"%d", diff);
			break;
		}
	}

	/* Resolve all labels in program */
	for(i=0;i<labelCount;i++){ /* for each label */
		for(j=0;j<instrCount;j++){ /* for each instruction */
			/* Resolve A-field label */
			if(strcmp(labels[i],instructions[j].a) == 0){
				diff = label_pos[i] - j;
				sprintf(instructions[j].a, "%d", diff);
			}
			/* Resolve B-field label */
			if(strcmp(labels[i],instructions[j].b) == 0){
				diff = label_pos[i] - j;
				sprintf(instructions[j].b, "%d", diff);
			}	
		}
	}

	return 0;
}

/**
 * hasAandB:
 *
 * Check whether or not an instruction has both fields or not
 *
 * PRE: instruction must a valid instr structure
 * POST: Returns 1 if both fields are present, 0 otherwise
 * 
 */
int hasAandB(struct instr instruction){
	if(instruction.a[0] != '\0' && instruction.b[0] != '\0'){
		return 1;
	}
	return 0;
}

/**
 * validate:
 *
 * Ensures all instructions from the Codemon program meet the constraints listed
 * in the codemon specifications
 *
 * PRE: instructions[] must contain parsed instructions from a Codemon program, with
 * 		all the labels removed.
 * POST: instructions[] contains a valid codemon program that satisfies all the given
 * 		 constraints.
 */
int validate(){
	int i;
	for(i=0;i<instrCount;i++){
		if(strcmp(instructions[i].opcode,"DAT") == 0){
			if(instructions[i].a[0] == '\0' && instructions[i].b[0] == '\0'){
				printf("ERROR: DAT cannot have two empty fields.\n");
				exit(1);
			}
			if(instructions[i].a[0] != '\0' && instructions[i].b[0] == '\0'){
				strcpy(instructions[i].b,instructions[i].a);
				instructions[i].bm = instructions[i].am;

				instructions[i].am = '\0';
				instructions[i].a[0] = '\0';
			}
			if(instructions[i].a[0] != '\0'){
				if(instructions[i].am != '#'){
					printf("ERROR: DAT fields can only be in immediate mode (#).\n");
					exit(1);
				}
			}
			if(instructions[i].b[0] != '\0'){
				if(instructions[i].bm != '#'){
					printf("ERROR: DAT fields can only be in immediate mode (#).\n");
					exit(1);
				}
			}
		} /* if DAT */

		else if(strcmp(instructions[i].opcode,"JMP") == 0){
			if(instructions[i].a[0] == '\0' && instructions[i].b[0] == '\0'){
				printf("ERROR: JMP cannot have two empty fields.\n");
				exit(1);
			}

			if(instructions[i].a[0] != '\0'){
				if(instructions[i].am == '#'){
					printf("ERROR: JMP A-field cannot be in immediate mode (#).\n");
					exit(1);
				}
			}
		} /* if JMP */
		else if(strcmp(instructions[i].opcode,"JMZ") == 0 || strcmp(instructions[i].opcode,"JMN") == 0
				|| strcmp(instructions[i].opcode,"DJN") == 0){
			if(!hasAandB(instructions[i])){
				printf("ERROR: %s must have both fields.\n",instructions[i].opcode);
				exit(1);
			}
			if(instructions[i].am == '#'){
				printf("ERROR: %s A-field cannot be in immediate mode (#).\n", instructions[i].opcode);
				exit(1);
			}
		} /* JMZ JMN DJN */
		else if(strcmp(instructions[i].opcode,"SET") == 0 || strcmp(instructions[i].opcode,"CLR") == 0
				|| strcmp(instructions[i].opcode,"NOP") == 0){
			if(instructions[i].a[0] != '\0' && instructions[i].b[0] == '\0'){
				strcpy(instructions[i].b,instructions[i].a);
				instructions[i].bm = instructions[i].am;

				instructions[i].am = '\0';
				instructions[i].a[0] = '\0';
			}
		} /* SET CLR NOP */
		else if(strcmp(instructions[i].opcode,"FRK") == 0) {
			if(instructions[i].a[0] == '\0'){
				printf("ERROR: %s must have an A-field.\n",instructions[i].opcode);
				exit(1);
			}
		} /* FRK */
		else {
			if(!hasAandB(instructions[i])) {
				printf("ERROR: %s must have both fields.\n",instructions[i].opcode);
				exit(1);
			}
		} /* All other instructions */
	} /* end of for */

	return 0;
} /* end of validate() */
