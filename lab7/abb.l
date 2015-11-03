%{
  #include <stdio.h>
  static int count;
%}

letter [a-z]

%option caseless

%%

{letter}.*     {count++;}
[ \t]       {}
\n          {}
.           {}

%%

int main(){
  count = 0;
  /*
  yyin = fopen("test.txt", "r");

  if (!yyin){
    yyin = stdin;
    printf("Failed to open file.\nDefaulting to stdin.");
  }
  */
  yylex();
  printf("identifiers found = %d\n", count);

  return 0;
}
