/**
 * packager.h:
 *
 * Definitions of variables and methods used to combine a parsed instruction
 * into binary data and output it.
 * 
 * @author Neivin Mathew
 * @version 1.0, 2015/10/02
 */
#ifndef PACKAGER_H
#define PACKAGER_H

#define MAXOPCODES 18
#define MAXADMODES 10


uint64 getOpcode(char *);
uint64 getAMode(char);
uint64 getA(char *);
uint64 getBMode(char);
uint64 getB(char *);
uint64 makeBinInstr(struct instr);
int outputBinary();
int assemble(char *);

#endif