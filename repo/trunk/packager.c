/**
 * packager.c:
 *
 * Packaging routines needed to convert parsed instructions into binary data
 * and output it to stdout.
 *
 * @author Neivin Mathew
 * @version 1.0, 2015/10/02
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "parser.h"
#include "checker.h"
#include "packager.h"


/* Lookup array for OPCODES */
char *opcodes[] =  {"DAT", "MOV", "ADD",
					"SUB", "MUL", "DIV",
					"MOD", "JMP", "JMZ",
					"JMN", "DJN", "SEQ",
					"SNE", "SLT", "SET",
					"CLR","FRK","NOP"};

/* Lookup array for Addressing modes */
char admodes[] = {'$', '#', '[', ']', '*',
				  '@', '{', '}', '<', '>'};

/* Lookup array for corresponding binary values */ 
int bin_vals[] =  { 0x00,0x01,0x02,
					0x03,0x04,0x05,
					0x06,0x07,0x08,
					0x09,0x0a,0x0b,
					0x0c,0x0d,0x0e,
					0x0f,0x10,0x11,};

/**
 * getOpcode:
 *
 * Convert a OPCODE string into its binary equivalent and bit-shift it
 * into the correct position.
 * 
 * PRE: opcode is present in opcodes[]
 * POST: opcode is converted to it's 64 bit binary equivalent.
 * 
 */
uint64 getOpcode(char * opcode){
	int i;
	uint64 op_bin = 0;

	for(i = 0 ; i < MAXOPCODES ; i++) {
		if(strcmp(opcode, opcodes[i]) == 0){
			op_bin = bin_vals[i];
			op_bin = op_bin << 58;
			break;
		}
	} /* for */

	return (op_bin);	
}

/**
 * getAMode:
 *
 * Convert an addressing mode character for the A-field into its binary
 * equivalent and bit-shift it into the correct position.
 * 
 * PRE: aMode is present in admodes[]
 * POST: aMode is converted to it's 64 bit binary equivalent.
 * 
 */
uint64 getAMode(char aMode){
	int i;
	uint64 a_mode_bin = 0;

	for (i = 0 ; i < MAXADMODES ; i++) {
		if(aMode == admodes[i]){
			a_mode_bin = bin_vals[i];
			a_mode_bin = a_mode_bin << 54;
			break;
		}
	}
	return (a_mode_bin);
}

/**
 * getA:
 *
 * Convert the A-field into its binary equivalent and bit-shift it
 * into the correct position.
 * 
 * PRE: a is an integer value
 * POST: a is normalized and converted into its binary equivalent.
 * 
 */
uint64 getA(char * a){
	uint64 a_bin = 0;

	a_bin = atoi(a);
	a_bin = a_bin % MEMSIZE; /* normalize field values */
	a_bin = a_bin << 29;

	return (a_bin);
}

/**
 * getBMode:
 *
 * Convert an addressing mode character for the B-field into its binary 
 * equivalent and bit-shift it into the correct position.
 * 
 * PRE: bMode is present in admodes[]
 * POST: bMode is converted to it's 64 bit binary equivalent.
 * 
 */
uint64 getBMode(char bMode){
	int i;
	uint64 b_mode_bin = 0;

	for (i = 0 ; i < MAXADMODES ; i++) {
		if(bMode == admodes[i]){
			b_mode_bin = bin_vals[i];
			b_mode_bin = b_mode_bin << 25;
			break;
		}
	}
	return (b_mode_bin);
}

/**
 * getB:
 *
 * Convert the B-field into its binary equivalent and bit-shift it
 * into the correct position.
 * 
 * PRE: b is an integer value
 * POST: b is normalized and converted into its binary equivalent.
 * 
 */
uint64 getB(char * b){
	uint64 b_bin = 0;

	b_bin = atoi(b);
	b_bin = b_bin % MEMSIZE; /* normalize field values */

	return (b_bin);
}

/**
 * makeBinInstr:
 *
 * Assemble all binary values of an instruction into a single 64 bit
 * binary value.
 *
 * PRE: instruction has only integer values in its fields
 * POST: The instruction is compiled into a 64 bit binary value
 */
uint64 makeBinInstr(struct instr instruction) {
	uint64 bin_instr = 0;

	bin_instr = getOpcode(instruction.opcode);
	bin_instr = bin_instr | getAMode(instruction.am);
	bin_instr = bin_instr | getA(instruction.a);
	bin_instr = bin_instr | getBMode(instruction.bm);
	bin_instr = bin_instr | getB(instruction.b);

	return (bin_instr);
}

/**
 * outputBinary:
 *
 * Write the begin value and the instruction binary values to stdout.
 *
 * PRE: instruction has only integer values in its fields
 * POST: The begin value and binary instructions are printed to stdout
 */
int outputBinary(){
	int i;
	/* beginVal is a number after resolveLabels() */
	/* Write beginVal to stdout */
	uint32 begin = atoi(beginVal);
	begin = begin % MEMSIZE;
	fwrite(&begin, sizeof(uint32), 1 , stdout);
	//printf("%d\n", begin);
	
	uint64 instructions_bin[instrCount];
	
	for (i=0;i<instrCount;i++){
		instructions_bin[i] = makeBinInstr(instructions[i]);
	}

	/* Write the array of binary instructions */
	fwrite(instructions_bin, sizeof(uint64), instrCount, stdout);

	return 0;
}

/**
 * assemble:
 *
 * PRE: filename must be an existing file that contains intructions that follow
 * 		the codemon specification.
 * POST: Contents of the file are parsed, validated and printed to stdout.
 */
int assemble(char * filename){
	parser(filename);
	resolveLabels();
	validate();
	outputBinary();

	return 0;
}


/*

int main(){
	parser("kraken.txt");

	printf("The begin value is:%s\n",beginVal);
	
	int i = 0;
	for (i=0;i<instrCount;i++){
		printf("%d\t",i);
		if(instructions[i].label[0] != '\0')
			printf("l:%s ", instructions[i].label);

		printf("op:%s ", instructions[i].opcode);
		printf("am:%c ", instructions[i].am);
		printf("a:%s ", instructions[i].a);
		printf("bm:%c ", instructions[i].bm);
		printf("b:%s\n", instructions[i].b);
	}
	
	resolveLabels();
	validate();

	printf("The begin value is:%s\n",beginVal);
	
	for (i=0;i<instrCount;i++){
		printf("%d\t",i);
		if(instructions[i].label[0] != '\0')
			printf("l:%s ", instructions[i].label);

		printf("op:%s ", instructions[i].opcode);
		printf("am:%c ", instructions[i].am);
		printf("a:%s ", instructions[i].a);
		printf("bm:%c ", instructions[i].bm);
		printf("b:%s\n", instructions[i].b);
	}

	outputBinary();

	return 0;
}

*/