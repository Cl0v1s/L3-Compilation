%{
	#include <stdio.h>
	#include <string.h>
	#include "include/Function.h"
	#include "include/Variable.h"
	#include "include/Env.h"
  #include "include/AST.h"

	int yyerror(char *s);
	int yylex();
	int yylineno;
%}

	%union {
		char* identity;
		int constant;
        struct Type* type;
        struct Variable* variable;
        struct Env* env;
        struct FuncDisclaimer* funcDisc;
        struct Func* function;
        struct FuncList* functions;
        struct Ast*  ast;
	}

	%token<identity>V
	%token<constant>I
	%token NewAr Sk T_ar T_boo T_int Def Dep Af true false Se If Th El Var Wh Do Pl Mo Mu And Or Not Lt Eq OPar CPar OBracket CBracket OBrace CBrace Comma Colon SpaceTab
	%start MP


  %type<ast> C
  %type<type> TP
  %type<env> L_argt L_argtnn Argt
  %type<funcDisc> D_entf D_entp
  %type<function> D
  %type<functions> LD
  %type<ast> E Et C

  

  %left Se
	%left Pl Mo
	%left Mu

%%


MP: L_vart LD C {}

E: E Pl E {}
  | E Mo E {}
  | E Mu E {}
  | E Or E {}
  | E Lt E {}
  | E Eq E {}
  | E And E {}
  | Not E {}
  | OPar E CPar {}
  | I {}
  | V {}
  | True {}
  | False {}
  | V OPar L_args CPar {}
  | NewAr TP OBracket E CBracket {}
  | Et {}

Et: V OBracket E CBracket {}
  | Et OBracket E CBracket {}

C: C Se C {}
  | Et Af E {}
  | V Af E {}
  | Sk {}
  | OBrace C CBrace {} 
  | If E Th C El C {}
  | Wh E Do C {}
  | V OPar L_args CPar {}

L_args: %empty {}
  | L_argsnn {}

L_argsnn: E {}
  | E Comma L_argsnn {}

L_argt: %empty { $$ = Env_init(); }
  | L_argtnn { $$ = $1;}

L_argtnn: Argt { $$ = $1;}
  | L_argtnn Comma Argt { $$ = Env_concat($1, $3); }

Argt: V Colon TP { $$ = Env_init(); Env_set_value($$, $1,Variable_init($3)); }

TP: T_boo { $$ = Type_init(BOOL, 0); }
  | T_int  { $$ = Type_init(INT, 0); }
  | T_ar TP { $$ = Type_init(ARRAY, $2); }

L_vart: %empty {  $$ = Env_init(); }
  | L_vartnn { $$ = $1;}

L_vartnn: Var Argt { $$ = $1; }
  | L_vartnn Comma Var Argt { $$ = Env_concat($1, $4); }

D_entp: Dep V OPar L_argt CPar { $$ = FuncDisclaimer_init($2, $4, Type_init(VOID, 0)); }

D_entf: Def V OPar L_argt CPar Colon TP { $$ = FuncDisclaimer_init($2, $4, $7); }

D: D_entp L_vart C { $$ = Func_init( $1, $2, $3); }
  | D_entf L_vart C { $$ = Func_init( $1, $2, $3); }

LD: %empty { $$ = FuncList_init(); }
  | LD D { $$ = $1; FuncList_append($$, $1); }

%%

int main()
{
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}
