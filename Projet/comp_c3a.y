%{
	#include <stdio.h>
	#include <string.h>
	#include "include/Quads.h"
	#include "include/Comp_C3A.h"
	#include "include/Env.h"

	int yyerror(char *s);
	int yylex();
	int yylineno;
%}

	%union {
		int constant;
		char* variable;
		struct Value* value;
		struct Quad* quad;
		struct QuadList* list;
	}
	%token<variable>V
	%token<constant>I
	%token Open Close Pl Mo Mu Af Afc Sk Jp Jz St Sp Se Minus Plus
	%start prog 

	%type<value> F FI
	%type<list> C
	%type<quad> O

    %left Se

	%left Pl Mo
	%left Mu
	%left Open
	

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0) */ 
prog: C	{ 
			C3A_Compile_Y86($1);	
	 	}
    ;


C: V Sp O { $3->address = $1; $$ = QuadList_create($3);}
| Sp O {$2->address = 0; $$ = QuadList_create($2);}
| C Se C { $$ = QuadList_concat($1, $3);}
| C Se {$$ = $1;}

O : Pl Sp F Sp F Sp V { $$ = Quad_create(0,Pl, $3, $5, $7); }
| Mo Sp F Sp F Sp V { $$ = Quad_create(0,Mo, $3, $5, $7); }
| Mu Sp F Sp F Sp V { $$ = Quad_create(0,Mu, $3, $5, $7); }
| Af Sp V Sp F Sp { $$ = Quad_create(0,Af, 0, $5, $3); } /* Ici on triche un peu, le premier argument des specs n'a de sens que si variable. Destination permettant de spécifier l'endroit ou stocker, on l'utilise ici */
| Afc Sp FI Sp Sp V { $$ = Quad_create(0,Afc, $3, 0, $6); }
| Sk Sp Sp Sp { $$ = Quad_create(0,Sk, 0, 0, 0); }
| Jp Sp Sp Sp V { $$ = Quad_create(0,Jp, 0, 0, $5); }
| Jz Sp F Sp Sp V { $$ = Quad_create(0,Jz, $3, 0, $6); }
| St Sp Sp Sp { $$ = Quad_create(0,St, 0, 0, 0); }

F: I {$$ = Value_create('I', &$1);}
| Minus I {$2 = $2*-1; $$ = Value_create('I', &$2);}
| Plus I {$$ = Value_create('I', &$2);}
| V { $$ = Value_create('V', $1);}

FI : I {$$ = Value_create('I', &$1);}
| Minus I {$2 = $2*-1; $$ = Value_create('I', &$2);}
| Plus I {$$ = Value_create('I', &$2);}
%%

int main()
{
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}