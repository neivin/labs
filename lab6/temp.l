%{
#include "y.tab.h"
%}
%%

heat			{return TOK_HEAT;}
on|off		{yylval.st = strdup(yytext); return TOK_STATE;}

target		{ return TOK_TARGET;}
temp 			{ return TOK_TEMP;}
[0-9]+ 		{ yylval.temp = atoi(yytext); return TOK_NUM;}

\n				{}
[ \t]			{}
.					{ return TOK_ERR; }

%%

/* 
yytext is whatver matched the regex
*/
