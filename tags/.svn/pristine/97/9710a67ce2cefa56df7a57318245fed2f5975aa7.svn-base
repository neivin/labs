/**
 * codemon.c:
 *
 * Main function to handle command line input to call the program.
 * Includes calls to other subroutines
 *
 * @author Neivin Mathew
 * @version 1.0, 2015/10/02
 * 
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "loader.h"
#include "parser.h"
#include "checker.h"
#include "packager.h"


int main(int argc, char *argv[])
{
	/* Simple bad call catch */
	if (argc < 3){
		printf("ERROR: Invalid call. Too few arguments.\n");
		return 1;
	}

	char option = argv[1][1];
	uint32 reportid;
	int limit;
	int no_of_players;

	switch(option) {
		/* Compile binary Codemon
		   char *fileName[] = argv[2] */
		case 'c':
			assemble(argv[2]);
			break;
		/* Test a codemon
		   filename = argv[2] limit = argv[3] */
		case 't':
			assert(isNumber(argv[3][0]));
			limit = atoi(argv[3]);
			assert(limit<=MAXTURNS);

			struct Codemon_pkg *cmon = loader(argv[2]);
			reportid = runTest(cmon, NULL, limit);
			printf("Codemon \"%s\" submitted to The Codex.\n", argv[2]);
			printf("Report ID = %d\n", reportid);
			free(cmon);
			break;
		/* Test 2 codemons
		   filename1 = argv2 file2 = argv3 limit = argv4 */
		case 's':
			assert(isNumber(argv[4][0]));
			limit = atoi(argv[4]);
			assert(limit<=MAXTURNS);

			struct Codemon_pkg *cmon1 = loader(argv[2]);
			struct Codemon_pkg *cmon2 = loader(argv[3]);

			reportid = runTest(cmon1, cmon2, limit);
			printf("The Codemons \"%s\" and \"%s\" were submitted to The Codex.\n", argv[2], argv[3]);
			printf("Report ID = %d\n", reportid);
			
			free(cmon1);
			free(cmon2);
			break;

		/* Submit a codemon for PvP
		   numPlayers = argv2 filename = argv3 */
		// Submit a codemon for PvP
		case 'p':
			assert(isNumber(argv[2][0]));
			no_of_players = atoi(argv[2]);
			assert(no_of_players>1);
			assert(no_of_players<5);

			struct Codemon_pkg *cmon3 = loader(argv[3]);

			reportid = runPvP(cmon3,no_of_players);
			printf("Report ID = %d\n", reportid);

			free(cmon3);

			break;
		/* Get the report from report ID
		   reportID = argv2 */
		case 'r':
			assert(isNumber(argv[2][0]));
			reportid = atoi(argv[2]);

			getReport(reportid,stdout);
			break;
		/* Catch incorrect command line calls */
		default:
			printf("ERROR: Invalid call. Incorrect call syntax");
			break;	
	}
	
	return 0;
}
