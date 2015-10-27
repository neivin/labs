%{

/*DEFINITIONS %% RULES %% USER CODE*/
#include <stdio.h>
static int linenum;

%}

%%

[1-9]*[0-9]+	{ printf("number\n"); return 0; }
[a-zA-Z]+	{ printf("word\n"); }
\n		{ linenum++; }
.		{ printf("Unexpected character\n"); }

%%

/*USER CODE*/
int main(){
	linenum = 1;
	yylex();
	printf("The number of lines are %d\n", linenum);	
	return 0;	
}
