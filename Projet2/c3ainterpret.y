%{
	#include <stdio.h>
	#include <string.h>
	#include "include/Quads.h"
	#include "include/C3A.h"
    #include "include/Env_C3A.h"

	int yyerror(char *s);
	int yylex();
	int yylineno;
%}

	%union {
	    char* identity;
        int constant;
        struct Env* env;
		struct Value* value;
		struct Quad* quad;
		struct QuadList* list;
	}

	%token<identity>V
	%token<constant>I
	%token Open Close Pl Mo Mu And Or Lt Not Af Afc AfInd Sk Jp Jz St Param Call Ret Ind Sp Se Minus Plus
	%start prog

	%type<value> F FI FF
	%type<list> C
	%type<quad> O

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0) */
prog: C	{
			struct EnvC3A* env = EnvC3A_init();
			C3A_run($1, 0, env, EnvC3A_init(), EnvC3A_init());
	 	}
    ;


C: V Sp O { $3->address = $1; $$ = QuadList_create($3);}
| Sp O {$2->address = 0; $$ = QuadList_create($2);}
| C Se C { $$ = QuadList_concat($1, $3);}
| C Se {$$ = $1;}

O : Pl Sp F Sp F Sp V { $$ = Quad_create(0,Pl, $3, $5, $7); }
| Mo Sp F Sp F Sp V { $$ = Quad_create(0,Mo, $3, $5, $7); }
| And Sp F Sp F Sp V { $$ = Quad_create(0,And, $3, $5, $7); }
| Lt Sp F Sp F Sp V { $$ = Quad_create(0,Lt, $3, $5, $7); }
| Or Sp F Sp F Sp V { $$ = Quad_create(0,Or, $3, $5, $7); }
| Not Sp F Sp Sp V { $$ = Quad_create(0, Not, $3, 0, $6); }
| Mu Sp F Sp F Sp V { $$ = Quad_create(0,Mu, $3, $5, $7); }
| Af Sp V Sp F Sp { $$ = Quad_create(0,Af, 0, $5, $3); } /* Ici on triche un peu, le premier argument des specs n'a de sens que si variable. Destination permettant de spécifier l'endroit ou stocker, on l'utilise ici */
| Afc Sp FI Sp Sp V { $$ = Quad_create(0,Afc, $3, 0, $6); }
| Sk Sp Sp Sp { $$ = Quad_create(0,Sk, 0, 0, 0); }
| Jp Sp Sp Sp V { $$ = Quad_create(0,Jp, 0, 0, $5); }
| Jz Sp F Sp Sp V { $$ = Quad_create(0,Jz, $3, 0, $6); }
| St Sp Sp Sp { $$ = Quad_create(0,St, 0, 0, 0); }
| AfInd Sp FF Sp F Sp V { $$ = Quad_create(0,AfInd, $3, $5, $7); }
| Ind Sp FF Sp F Sp V { $$ = Quad_create(0, Ind, $3, $5, $7); }
| Param Sp FF Sp F Sp { $$ = Quad_create(0,Param, $3, $5, 0); }
| Call Sp V Sp FI Sp { $$ = Quad_create(0,Call, 0, $5, $3); }
| Ret Sp Sp Sp { $$ = Quad_create(0,Ret, 0, 0, 0); }


FF: V { $$ = Value_create('V', $1);}


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