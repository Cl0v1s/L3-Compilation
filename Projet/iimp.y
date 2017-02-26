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
	%token<variable> V
	%token<constante> I
	%token Af Sk Se If Th Wh Do Pl Mo Mu
	%type<node> C0 C E T F
	%nonassoc Th
	%nonassoc El
	%left '('
	%start prog 

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0)  */
prog: C	{ 
	 		Env env;
			Env_init(&env);
			Ast_run($1, &env);
	 	}
    ;

E: E Pl T
| E Mo T 
| T
;

T: T Mu F
| F
;

F: "(" E ")"
| I
| V
;

C0: V Af E		
 | Sk			
 | Se			
 | '(' C ')'		
 | If E Th C El C0	
 | Wh E Do C0		
 ;

C: C Se C0		
 | C0			
 | '(' C0 ')'

%%

int main()
{
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}