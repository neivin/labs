%{
#include <stdio.h>

/* put this in whatver calls*/
int yylex(void);


void yyerror(const char* err) {
	fprintf(stderr, "Error: %s\n", err);	
}

%}

%token TOK_HEAT TOK_TARGET TOK_TEMP TOK_ERR
%union {
	int temp;
	char* st;
}

%token <st> TOK_STATE
%token <temp> TOK_NUM

%%

commands: commands command
	|
	;

command: heat_stmt
	| temp_set
	| err
	;

heat_stmt: TOK_HEAT TOK_STATE { printf("Heat turned %s\n", yylval.st); free(yylval.st); }
	 ;

temp_set: TOK_TARGET TOK_TEMP TOK_NUM  { printf("Temperature was set to %d\n", yylval.temp); }
	;

err: TOK_ERR { yyerror("Unrecognized token\n"); }

%%
/*
commands -> commands command
		|		
		commands command

MAIN HERE:----		
*/

int main(){
	yyparse();
	return 0;
}
