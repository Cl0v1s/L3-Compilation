%{
	#include <stdio.h>
	#include "include/Ast.h"
	#include "include/IMP.h"
	#include "include/Env.h"

	int yyerror(char *s);
	int yylex();
	int yylineno;
%}

	%union {
		int constant;
		char* variable;
		struct Ast *node;
	}
	%token<variable>V
	%token<constant>I
	%token Open Close Pl Mo Mu Af Afc Sk Jp Jz St Sp Se
	%start prog 

    %left Se

	%left Pl Mo
	%left Mu
	%left Open
	

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0) */ 
prog: C	{ 

	 	}
    ;


C: V Sp O
| Sp O
| C Se C
| C Se

O : Pl Sp F Sp F Sp V
| Mo Sp F Sp F Sp V
| Mu Sp F Sp F Sp V
| Af Sp F Sp F Sp
| Afc Sp I Sp Sp V
| Sk Sp Sp Sp
| Jp Sp Sp Sp V
| Jz Sp F Sp Sp V
| St Sp Sp Sp

F: I
| V



%%

int main()
{
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}