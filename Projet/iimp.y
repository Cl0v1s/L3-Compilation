%{
	#include <stdio.h>

	int yyerror(char *s);
	int yylex();
	int yylineno;
%}

	%token I
	%token V
	%token AF SK SE IF TH EL WH DO PL MO MU OPEN CLOSE
	%token EOL
%%

E: E PL T
| E MO T
| T

T: T MU F
| F

F: OPEN E CLOSE
| I
| V

C : V AF E
| SK
| OPEN C CLOSE
| IF E TH C EL C
| WH E DO C
| C SE C


%%

int main()
{
	yyparse();
}

int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}