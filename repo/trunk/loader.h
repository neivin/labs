/**
 * loader.h:
 *
 * Definitions of methods used in loading a binary codemon.
 * 
 * @author Neivin Mathew
 * @version 1.0, 2015/10/02
 */
#ifndef LOADER_H
#define LOADER_H

int verifyFilename(char *);
struct Codemon_pkg *loader(char *);

#endif
