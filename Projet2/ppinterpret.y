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
		struct Variable* variable;
    struct Env* environment;
    struct Quad* quad;
	}

	%token<variable>V
	%token<constant>I
	%token C Pl Mo Mu Af Sk Jp Jz St Sp Se Minus Plus
	%start prog

	%type<value> F FI
	%type<list> C

  %left Se
	%left Pl Mo
	%left Mu

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0) */
prog: C	{
			// TODO : Appels des fonctions d'interpretation
	 	}
    ;

MP: L_vart LD C

E: E Pl E
  | E Mo E
  | E Mu E
  | E Or E
  | E Lt E
  | E Eq E
  | E And E
  | Not E
  | OPar E CPar
  | I
  | V
  | true
  | false
  | V OPar L_args CPar
  | NewAr TP OBracket E CBracket
  | Et

Et: V OBracket E CBracket
  | Et OBracket E CBracket

C: C Se C
  | Et Af E
  | V Af E
  | Sk
  | OBrace C CBrace
  | If E Th C El C
  | Wh E Do C
  | V OPar L_args CPar

L_args: %empty
  | L_argsnn

L_argsnn: E
  | E Comma L_argsnn

L_argt: %empty
  | L_argtnn

L_argtnn: Argt
  | L_argtnn Comma Argt

Argt: V Colon TP

TP: T_boo
  | T_int
  | T_ar TP

L_vart: %empty
  | L_vartnn

L_vartnn: Var Argt
  | L_vartnn Comma Var Argt

D_entp: Dep NPro OPar L_argt CPar

D_entf: Def NFon OPar L_argt CPar Colon TP

D: D_entp L_vart C
  | D_entf L_vart C

LD: %empty
  | LD D

%%

int main()
{
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}
